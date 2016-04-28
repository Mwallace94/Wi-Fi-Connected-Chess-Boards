#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define EMPTY 0

#define BPAWN 1
#define BROOK 2
#define BKNIGHT 3
#define BBISHOP 4
#define BQUEEN 5
#define BKING 6

#define WPAWN 7
#define WROOK 8
#define WKNIGHT 9
#define WBISHOP 10
#define WQUEEN 11
#define WKING 12

#define BROWS 8
#define BCOLS 12

#define BLACK 0
#define WHITE 6

typedef struct{
  char piece;
  int fromRow;
  int fromCol;
  int toRow;
  int toCol;
} transition;

int yourcolor;
int theircolor;
char takenPiece;
char** state[BROWS][BCOLS];
char** teststate[BROWS][BCOLS];
int enpassantB = 0;
int enpassantW = 0;
int kingBMovedOnce = 0;
int kingWMovedOnce = 0;
int leftRookBMovedOnce = 0;
int leftRookWMovedOnce = 0;
int rightRookBMovedOnce = 0;
int rightRookWMovedOnce = 0;
int castleConfirmed = 0;
int testing = 0;
transition tprev;
char goodMove[9];

void initStartState();
void printState();
void printStateNoGrave();
void zeroState();
transition compareStates();
int isLegal(transition t);
void moveToGraveyard(char piece);
void castlingMaintenance();
int isCheckForEnemy();
int isCheckForYou();
int isCheckMate(transition t);
void restoreMove(transition t);
int checkKingSurrounding(transition t);
int checkBlockKing(transition t);
int checkSaveKing(transition t);
int moverightcolor(int piece);
void playturn();
char getPieceFromPos(int fromX, int fromY);

int main(int argc, char* argv[]) {
  yourcolor = WHITE;
  theircolor = BLACK;
  initStartState();
  printState();

  //used to test moves with transitions
  playturn();

  //printState();
  return 1;
}

char getPieceFromPos(int fromX, int fromY) {

	return state[fromX][fromY];
}

//allows user to play the game based on input
void playturn() {
  //int goodMove[1];
	//moved to global
  int reset;
  int listen_fd;
  struct sockaddr_in servaddr;
  listen_fd = socket(AF_INET, SOCK_STREAM,0);
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htons(INADDR_ANY);
  servaddr.sin_port = htons(656);
  bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
  listen(listen_fd,5);

  struct sockaddr_in client;
  socklen_t clientSize;
  int comm_fd = accept(listen_fd,(struct sockaddr*)&client, &clientSize);
  printf("comm_fd = %d\n", comm_fd);
  close(listen_fd);
  char str[4];
  bzero(str,4);

  transition t; 
  int gameOn = 1;
  while(gameOn) {
    initTestState();
    int move = 0;
    int isCheck = 0;
    while(move == 0) {
      for(reset = 0; reset < 9; reset++) {
      	goodMove[reset] = '\0';
      }
      initTestState();
      //if(scanf("%d %d %d %d %d", &t.piece, &t.fromRow, &t.fromCol, &t.toRow, &t.toCol) == EOF)  return;
      if(read(comm_fd,str,4*sizeof(char)) == 0) {
      	printf("Read Error\n");
      	return;
      }
/*
      int i;
      for(i=0;i<5;i++) { printf("%s ", str[i]); }
      printf("\n");
*/
      printf("Finished Reading\n");
      t.fromRow = (int) str[0]; 
      t.fromCol = (int) str[1]; 
      t.piece = getPieceFromPos(t.fromRow, t.fromCol);
      t.toRow =  (int) str[2];
      t.toCol =  (int) str[3];
      printf("move(%c %d %d %d %d)\n", t.piece, t.fromRow, t.fromCol, t.toRow, t.toCol);
      if(t.piece == 0) printStateNoGrave();
      takenPiece = '\0';
      move = isLegal(t);
      printf("\nIs the move legal?:%d\n\n", move);
      if(move) {
      	isCheck = testMoveForCheck(t);
      	if(isCheck) {
        	move = 0;
      	}
      }
      if(!move){
      	goodMove[0] = 0;
        write(comm_fd,goodMove,9);
      	//change write to write to comm_fd(goodmove, 2 potential moves)
      }
    	
	  }
    
      teststate[t.fromRow][t.fromCol] = EMPTY;
      teststate[t.toRow][t.toCol] = t.piece;
      if(enpassantW){
        teststate[t.toRow-1][t.toCol] = EMPTY;
        enpassantW = 0;
      }else if(enpassantB){
        teststate[t.toRow+1][t.toCol] = EMPTY;
        enpassantB = 0;
      }
      if(castleConfirmed){
        if(castleConfirmed == 1){
          teststate[0][2] = EMPTY;
          teststate[0][5] = WROOK;
        }else if(castleConfirmed == 2){
          teststate[0][9] = EMPTY;
          teststate[0][7] = WROOK;
        }else if(castleConfirmed == 3){
          teststate[7][2] = EMPTY;
          teststate[7][5] = BROOK;
        }else if(castleConfirmed == 4){
          teststate[7][9] = EMPTY;
          teststate[7][7] = BROOK;
        }
        castleConfirmed = 0;
      }
     
	    printState();
      printf("\n");

       //promotion
      if(yourcolor == WHITE && t.toRow == 7 && t.piece ==WPAWN){
      	printf("Pawn is up for promotion\n");
      	goodMove[0] = 2;
      	tprev.piece = t.piece;
        tprev.fromRow = t.fromRow;
        tprev.fromCol = t.fromCol;
        tprev.toRow = t.toRow;
        tprev.toCol = t.toCol;
        teststate[t.toRow][t.toCol] = WQUEEN;
        write(comm_fd,goodMove,9);

      	/*goodMove[0] =  2;
      	write(comm_fd,goodMove,9);
      	if(read(comm_fd,str,1*sizeof(char)) == 0) {
      		printf("Read Error\n");
      		return;
      	}
      	int promocase = (int) str[1];
      	if(promocase == 1){
      		teststate[t.toRow][t.toCol] = 11;//queen
      	}else if(promocase == 2){
      		teststate[t.toRow][t.toCol] = 10;//bishop
      	}else if(promocase == 3){
			teststate[t.toRow][t.toCol] = 9;//knight
      	}else if(promocase == 4){
      		teststate[t.toRow][t.toCol] = 8;//rook
      	}*/
      }

      //promotion
      else if(yourcolor == BLACK && t.toRow == 0 && t.piece == BPAWN){
      	printf("Pawn is up for promotion\n");
      	goodMove[0] = 2;
      	 tprev.piece = t.piece;
        tprev.fromRow = t.fromRow;
        tprev.fromCol = t.fromCol;
        tprev.toRow = t.toRow;
        tprev.toCol = t.toCol;
        teststate[t.toRow][t.toCol] = BQUEEN;
        write(comm_fd,goodMove,9);

      	/*goodMove[0] =  2;
      	write(comm_fd,goodMove,9);
      	if(read(comm_fd,str,1*sizeof(char)) == 0) {
      		printf("Read Error\n");
      		return;
      	}
      	int promocase = (int) str[1];
      	if(promocase  == 1){
      		teststate[t.toRow][t.toCol] = 5;//queen
      	}else if(promocase  == 2){
      		teststate[t.toRow][t.toCol] = 4;//bishop
      	}else if(promocase == 3){
			teststate[t.toRow][t.toCol] = 3;//knight
      	}else if(promocase  == 4){
      		teststate[t.toRow][t.toCol] = 2;//rook
      	}*/
      }

      else{
      	goodMove[0] = 1;
    	  tprev.piece = t.piece;
        tprev.fromRow = t.fromRow;
        tprev.fromCol = t.fromCol;
        tprev.toRow = t.toRow;
        tprev.toCol = t.toCol;
    	  write(comm_fd,goodMove,9);
      }
   
      int i, j;
      for(i = 0; i < BROWS; i++) {
        for(j = 0; j < BCOLS; j++) {
          state[i][j] = teststate[i][j];
        }
      }
      castlingMaintenance();
      printTestState();
      
      int checkmate = isCheckForEnemy(t);
      if(checkmate == 1){
        printf("Opponent has been placed in check\n\n\n");
      }else if(checkmate == 2){
        gameOn = 0;
        printf("Opponent has been placed in checkmate\n\n\n");
      }else{
        printf("Opponent has not been placed in check\n\n\n");
      }

    if(yourcolor == WHITE) {yourcolor = BLACK; theircolor = WHITE;}
    else if(yourcolor == BLACK) {yourcolor = WHITE; theircolor = BLACK;}
  }
}

//creates the start state repreentation of chess
void initStartState() {
  zeroState();
  int i;
  for(i = 2; i <= 9; i++) {
    state[1][i] = WPAWN;
    state[6][i] = BPAWN;
  }
  state[0][2] = WROOK;
  state[0][3] = WKNIGHT;
  state[0][4] = WBISHOP;
  state[0][5] = WQUEEN;
  state[0][6] = WKING;
  state[0][7] = WBISHOP;
  state[0][8] = WKNIGHT;
  state[0][9] = WROOK;

  state[7][2] = BROOK;
  state[7][3] = BKNIGHT;
  state[7][4] = BBISHOP;
  state[7][5] = BQUEEN;
  state[7][6] = BKING;
  state[7][7] = BBISHOP;
  state[7][8] = BKNIGHT;
  state[7][9] = BROOK;
}


void initTestState(){
  int i,j;
  for(i = 0; i < 8; i++){
    for(j = 0; j < 12; j++){
      teststate[i][j] = state[i][j];
    }
  }
}

int testMoveForCheck(transition t){
	goodMove[1] = (char)t.fromRow; 
  	goodMove[2] = (char)t.fromCol;
  	goodMove[3] = (char)t.toRow;
  	goodMove[4] = (char)t.toCol;

  if(teststate[t.toRow][t.toCol] != '\0'){
  	goodMove[5] = (char)t.toRow;
  	goodMove[6] = (char) t.toCol;
    moveToGraveyard(teststate[t.toRow][t.toCol]);
  }
  teststate[t.fromRow][t.fromCol] = EMPTY;
  teststate[t.toRow][t.toCol] = t.piece;
  if(enpassantW){
  	goodMove[5] = (char)t.toRow-1;
  	goodMove[6] = (char) t.toCol;
    moveToGraveyard(state[t.toRow-1][t.toCol]);
    teststate[t.toRow-1][t.toCol] = EMPTY;
  }else if(enpassantB){
  	goodMove[5] = (char)t.toRow+1;
  	goodMove[6] = (char) t.toCol;
    moveToGraveyard(state[t.toRow+1][t.toCol]);
    teststate[t.toRow+1][t.toCol] = EMPTY;
  }  
  if(castleConfirmed){
    if(castleConfirmed < 1 || castleConfirmed > 4){
      //printf("Castling # %d \n\n\n", castleConfirmed);
      //printf("What happened?\n\n\n");
      exit(-1);
    }else{
      if(castleConfirmed == 1){
        teststate[0][2] = EMPTY;
        teststate[0][5] = WROOK;
        goodMove[5] = (char)0;
  		  goodMove[6] = (char)2;
  		  goodMove[7] = (char)0;
  		  goodMove[8] = (char)5;
      }else if(castleConfirmed ==2){
        teststate[0][9] = EMPTY;
        teststate[0][7] = WROOK;
        goodMove[5] = (char)0;
  		  goodMove[6] = (char)9;
  		  goodMove[7] = (char)0;
  		  goodMove[8] = (char)7;
      }else if(castleConfirmed ==3){
        teststate[7][2] = EMPTY;
        teststate[7][5] = BROOK;
        goodMove[5] = (char)7;
  		  goodMove[6] = (char)2;
  		  goodMove[7] = (char)7;
  		  goodMove[8] = (char)5;
      }else if(castleConfirmed == 4){
        teststate[7][9] = EMPTY;
        teststate[7][7] = BROOK;
        goodMove[5] = (char)7;
  		  goodMove[6] = (char)9;
  		  goodMove[7] = (char)7;
  		  goodMove[8] = (char)7;
      }
    }
  }
    int check = isCheckForYou();
    if(check == 1){
      enpassantW = 0;
      enpassantB = 0;
      castleConfirmed =0;
      return 1;
    }
  return 0;
  
}

//prints the current state out, testing purposes
void printState() {
  int i, j;
  for(i = 0; i < BROWS; i++) {
    for(j = 0; j < BCOLS; j++) {
      printf("%d\t", (int) state[i][j]);
    }
    printf("\n");
  }
}

//same as above without gravyard pieces, test
void printStateNoGrave() {
  int i, j;
  for(i = 0; i < BROWS; i++) {
    for(j = 2; j < BCOLS-2; j++) {
      printf("%d\t", (int) state[i][j]);
    }
    printf("\n");
  }
}

//prints testboard
void printTestState() {
  int i, j;
  for(i = 0; i < BROWS; i++) {
    for(j = 0; j < BCOLS; j++) {
      printf("%d\t", (int) teststate[i][j]);
    }
    printf("\n");
  }
}

// zeros out a state
void zeroState() {
  int i, j;
  for(i = 0; i < BROWS; i++) {
    for(j = 0; j < BCOLS; j++) {
      state[i][j] = 0;
    }
  }
}

//detects youre moving the right color
int moverightcolor(int piece) {
  if(piece >= 1 && piece <= 6 && yourcolor == BLACK) return 1;
  if(piece >= 7 && piece <= 12 && yourcolor == WHITE) return 1;
  if(testing) return 1;
  return 0;
}

//detects if current move is legal
int isLegal(transition t) {
  int ydis = abs(t.fromRow - t.toRow); //ydistance
  int xdis = abs(t.fromCol - t.toCol);//x distance
  int dis = ydis + xdis;//x +y

  if(!moverightcolor(t.piece)) return 0;
  if(t.toRow- t.fromRow == 0 && t.toCol - t.fromCol == 0) return 0;
  //only important for which color you are, but this is ambiguous at the time. AKA will black and white be always on same side or user disgression.
  //will create both directions I suppose, but will be white towards player and black away for not
  if(t.piece == WPAWN) {
    int ydist = t.toRow - t.fromRow;
    int xdist = t.toCol - t.fromCol;
    //should always be true for move only
    if(ydist == 1 && !xdis && (teststate[t.toRow][t.toCol] == '\0')) return 1;
    else if(t.fromRow == 1 && ydist == 2 && xdist == 0 && (teststate[t.toRow][t.toCol] == '\0') && (teststate[t.toRow-1][t.toCol] == '\0')) return 1;
    //taking a piece
    else if(ydist == 1 && abs(xdist) == 1 && (teststate[t.toRow][t.toCol] != '\0')) {
      if(teststate[t.toRow][t.toCol] >= 1 &&  teststate[t.toRow][t.toCol] <= 6){
        return 1;
      }
	  return 0;
	}
	//enpassant 
      else if(ydist == 1 && abs(xdist) == 1 && teststate[t.fromRow][t.toCol] == BPAWN && (t.fromRow == 4)){
      if(tprev.piece == BPAWN && tprev.fromRow == 6 && tprev.toRow == 4){
            enpassantW = 1;
            return 1;
        }
       return 0;
	}
    else{
		return 0;
	}
  }
 if(t.piece == BPAWN) {
   int ydist = t.fromRow - t.toRow;
   int xdist = t.toCol - t.fromCol;
   //should always be true for move only
   if(ydist == 1 && !xdis && (teststate[t.toRow][t.toCol] == '\0')) return 1;
   else if(t.fromRow == 6 && ydist == 2 && xdist == 0 && (teststate[t.toRow][t.toCol] == '\0') && (teststate[t.toRow+1][t.toCol] == '\0')) return 1;
   //add taking piece here

   else if(ydist == 1 && abs(xdist) == 1 && (teststate[t.toRow][t.toCol] != '\0')){
     if(teststate[t.toRow][t.toCol]  >= 7 && teststate[t.toRow][t.toCol] <= 12){
       return 1;
     }
	 return 0;
   }
	 //enpassant
     else if(ydist == 1 && abs(xdist) == 1 && teststate[t.fromRow][t.toCol] == WPAWN && (t.fromRow == 3)){
        if(tprev.piece == WPAWN && tprev.fromRow == 1 && tprev.toRow == 3){
            enpassantB = 1;
            return 1;
        }
       return 0;
	}
	else {
	   return 0;
   }
 }
  if(t.piece == WROOK || t.piece == BROOK) {
   //detects if move is up or down or left or right but not both
   if(ydis && xdis) {
     return 0;
     //detects collision for move only
     //xdir
   } else if(ydis) {
     int fromltto;
     if(t.fromRow < t.toRow) fromltto = 1;
     else fromltto = 0;
     if(fromltto) {
       int i;
       //change t.toRow and the rest when determining taking a piece
	    for(i = t.fromRow+1; i <= t.toRow; i++) {
         if((i == t.toRow) && teststate[i][t.fromCol] != '\0'){
           if(t.piece == WROOK && teststate[i][t.fromCol] >= 1 && teststate[i][t.fromCol] <= 6){
             return 1;
           }
           else if(t.piece == BROOK && teststate[i][t.fromCol] >= 7 && teststate[i][t.fromCol] <= 12){
             return 1;
           }
           return 0;
         }
         else if((i == t.toRow) && teststate[i][t.fromCol] == '\0'){
           return 1;
         }

         if(teststate[i][t.fromCol] != '\0') return 0;
       }
     } else {
       if(t.fromRow == t.toRow) return 0;
       int i;
       for(i = t.fromRow-1; i >= t.toRow; i--) {
         if((i == t.toRow) && teststate[i][t.fromCol] != '\0'){
           if(t.piece == WROOK && teststate[t.toRow][t.toCol] >= 1 && teststate[t.toRow][t.toCol] <= 6){
             return 1;
           }
           else if(t.piece == BROOK && teststate[t.toRow][t.toCol] >= 7 && teststate[t.toRow][t.toCol] <= 12){
             return 1;
           }
		   
           return 0;
         }
         else if((i == t.toRow) && teststate[t.toRow][t.fromCol] == '\0'){
           return 1;
         }

         if(teststate[i][t.fromCol] != '\0') {
			 return 0;
		 }
       }
     }
  //ydir
   } else if(xdis) {
     int fromltto;
     if(t.fromCol < t.toCol) fromltto = 1;
     else fromltto = 0;
     if(fromltto) {
       int i;
       for(i = t.fromCol+1; i <= t.toCol; i++) {
         if((i == t.toCol) && teststate[t.fromRow][i] != '\0'){
           if(t.piece == WROOK && teststate[t.fromRow][i] >= 1 && teststate[t.fromRow][i] <=6){
             return 1;
           }
           else if(t.piece == BROOK && teststate[t.fromRow][i] >= 7 && teststate[t.fromRow][i] <= 12){
             return 1;
           }
           return 0;
         }
         else if((i == t.toCol) && teststate[t.fromRow][i] == '\0'){
           return 1;
         }

         if(teststate[t.fromRow][i] != '\0') return 0;
       }
     }
	  else {
       if(t.fromCol == t.toCol) return 0;
       int i;
       for(i = t.fromCol-1; i >= t.toCol; i--) {
         if((i == t.toCol) && teststate[t.fromRow][i] != '\0'){
           if(t.piece == WROOK && teststate[t.fromRow][i] >= 1 && teststate[t.fromRow][i] <= 6){
             return 1;
           }
           else if(t.piece == BROOK && teststate[t.fromRow][i] >= 7 && teststate[t.fromRow][i] <= 12){
             return 1;
           }
           return 0;
         }
         else if((i == t.toCol) && teststate[t.fromRow][t.toCol] == '\0'){
           return 1;
         }
         if(teststate[t.fromRow][i] != '\0') return 0;
       }
     }
   }
   return 1;
 }

 if(t.piece == WKNIGHT || t.piece == BKNIGHT) {
   //detects move only
   if(ydis && xdis && (dis == 3) && teststate[t.toRow][t.toCol] == '\0') {
     return 1;
   }else if(ydis && xdis && dis == 3 && teststate[t.toRow][t.toCol] != '\0'){
     if(teststate[t.toRow][t.toCol] >= 1 && teststate[t.toRow][t.toCol] <= 6 && t.piece == WKNIGHT){
       return 1;
     } else if(teststate[t.toRow][t.toCol] >= 7 && teststate[t.toRow][t.toCol] <= 12 && t.piece == BKNIGHT){
       return 1;
     }
     return 0;
   }
   else return 0;
 }
 //checks bishop moved diagnally and no collision
 if(t.piece == BBISHOP || t.piece == WBISHOP) {
   int i;
   if(ydis != xdis) {
     return 0;
   } else if(t.fromRow < t.toRow && t.fromCol < t.toCol) {
     for(i = 1; i <= ydis; i++) {
       if(teststate[t.fromRow+i][t.fromCol+i] != '\0' && (i != ydis)) return 0;
       else if(i == ydis){
         if(t.piece == BBISHOP && teststate[t.fromRow+i][t.fromCol+i] != '\0'&& teststate[t.fromRow+i][t.fromCol+i] >=7 && teststate[t.fromRow+i][t.fromCol+i] <= 12){
           return 1;
         }else if(t.piece == WBISHOP && teststate[t.fromRow+i][t.fromCol+i] != '\0'&& teststate[t.fromRow+i][t.fromCol+i] >=1 && teststate[t.fromRow+i][t.fromCol+i] <= 6){
           return 1;
         }else if((t.piece == WBISHOP || t.piece== BBISHOP) && teststate[t.fromRow+i][t.fromCol+i] == '\0'){
			 return 1;
		 }
		 else{
           return 0;
         }
       }
     }
 } else if(t.fromRow > t.toRow && t.fromCol < t.toCol) {
     for(i = 1; i <= ydis; i++) {
       if(teststate[t.fromRow-i][t.fromCol+i] != '\0' && (i != ydis)) return 0;
       else if(i == ydis){
         if(t.piece == BBISHOP && teststate[t.fromRow-i][t.fromCol+i] != '\0'&& teststate[t.fromRow-i][t.fromCol+i] >=7 && teststate[t.fromRow-i][t.fromCol+i] <= 12){
           return 1;
         }else if(t.piece == WBISHOP && teststate[t.fromRow-i][t.fromCol+i] != '\0'&& teststate[t.fromRow-i][t.fromCol+i] >=1 && teststate[t.fromRow-i][t.fromCol+i] <= 6){
           return 1;
         }else if((t.piece == WBISHOP || t.piece== BBISHOP) && teststate[t.fromRow-i][t.fromCol+i] == '\0'){
			 return 1;
		 }else{
           return 0;
         }
       }
     }
 } else if(t.fromRow < t.toRow && t.fromCol > t.toCol) {
     for(i = 1; i <= ydis; i++) {
       if(teststate[t.fromRow+i][t.fromCol-i] != '\0' && (i != ydis)) return 0;
       else if(i == ydis){
         if(t.piece == BBISHOP && teststate[t.fromRow+i][t.fromCol-i] != '\0'&& teststate[t.fromRow+i][t.fromCol-i] >=7 && teststate[t.fromRow+i][t.fromCol-i] <= 12){
           return 1;
         }else if(t.piece == WBISHOP && teststate[t.fromRow+i][t.fromCol-i] != '\0'&& teststate[t.fromRow+i][t.fromCol-i] >=1 && teststate[t.fromRow+i][t.fromCol-i] <= 6){
           return 1;
         }else if((t.piece == WBISHOP || t.piece== BBISHOP) && teststate[t.fromRow+i][t.fromCol-i] == '\0'){
			 return 1;
		 }else{
           return 0;
         }
       }
     }
 } else if(t.fromRow > t.toRow && t.fromCol > t.toCol) {
     for(i = 1; i <= ydis; i++) {
       if(teststate[t.fromRow-i][t.fromCol-i] != '\0' && (i != ydis)) return 0;
       else if(i == ydis){
         if(t.piece == BBISHOP && teststate[t.fromRow-i][t.fromCol-i] != '\0'&& teststate[t.fromRow-i][t.fromCol-i] >=7 && teststate[t.fromRow-i][t.fromCol-i] <= 12){
           return 1;
         }else if(t.piece == WBISHOP && teststate[t.fromRow-i][t.fromCol-i] != '\0'&& teststate[t.fromRow-i][t.fromCol-i] >=1 && teststate[t.fromRow-i][t.fromCol-i] <= 6){
           return 1;
         }else if((t.piece == WBISHOP || t.piece== BBISHOP) && teststate[t.fromRow-i][t.fromCol-i] == '\0'){
			 return 1;
		 }else{
           return 0;
         }
       }
     }
   }
   return 1;
 }
//checks queen against both bishop and rooks moves. If satisfies one we guchi.
 if(t.piece == BQUEEN || t.piece == WQUEEN) {
   if(t.piece == BQUEEN){ 
	   t.piece = BROOK;
   }
   else if(t.piece == WQUEEN){
	   t.piece = WROOK;
   }
   if(isLegal(t)) return 1;
   if(t.piece == BROOK) t.piece = BBISHOP;
   if(t.piece == WROOK) t.piece = WBISHOP;
   if(isLegal(t)) return 1;
   return 0;
 }
 
if(t.piece == BKING || t.piece == WKING) {
   if((dis == 1 || (dis == 2 && (xdis && ydis))) && teststate[t.toRow][t.toCol] == '\0'){
	   //printf("Position 1\n\n\n");
      if(t.piece == BKING){
        kingBMovedOnce  = 1;
      }else if(t.piece == WKING){
        kingWMovedOnce = 1;
      }
    return 1;
   }
   else if((dis == 1  || (dis == 2 && (xdis && ydis)))&& teststate[t.toRow][t.toCol] != '\0'){
     if(t.piece == WKING && teststate[t.toRow][t.toCol] >= 1 && teststate[t.toRow][t.toCol] <= 6){
      if(t.piece == WKING){
        kingWMovedOnce = 1;
      }
           //printf("Position 2\n\n\n");
       return 1;
     }else if(t.piece == BKING && teststate[t.toRow][t.toCol] >= 7 && teststate[t.toRow][t.toCol] <= 12){
        kingBMovedOnce  = 1;
           //printf("Position 3\n\n\n");
       return 1;
     }
	 
     return 0;
   }else if(dis == 2 && ydis == 0){ 
     if((kingWMovedOnce == 0) && t.piece == WKING && t.fromRow == 0 && t.fromCol == 6){
       if(!leftRookWMovedOnce && (t.toCol < t.fromCol) && (teststate[0][3] == '\0' && teststate[0][4] == '\0' && teststate[0][5] == '\0') && teststate[0][2] == WROOK){
         castleConfirmed = 1;
        printf("Castling");

         //printf("Castling # 1\n\n\n");
         return 1;
	   }else if(!rightRookWMovedOnce && (t.toCol > t.fromCol) && (teststate[0][7] == '\0' && teststate[0][8] == '\0') && teststate[0][9] == WROOK){
		     castleConfirmed = 2;
          printf("Castling");

         //printf("Castling # 2\n\n\n");
         return 1;
       }
     }else if((kingBMovedOnce == 0) && t.piece == BKING && t.fromRow == 7 && t.fromCol == 6){
       if(!leftRookBMovedOnce && (t.toCol < t.fromCol) && (teststate[7][3] == '\0' && teststate[7][4] == '\0' && teststate[7][5] == '\0') && teststate[7][2] == BROOK){
		    castleConfirmed = 3;
     printf("Castling");

        //printf("Castling # 3\n\n\n");
         return 1;
       }else if(!rightRookBMovedOnce && (t.toCol > t.fromCol) && (teststate[7][7] == '\0' && teststate[7][8] == '\0') && teststate[7][9] == BROOK){
         castleConfirmed = 4;
         printf("Castling");

         //printf("Castling # 4\n\n\n");
         return 1;
       }
     }else{
      //printf("WTF\n\n\n");
       return 0;
     }
   }
   
   else{
	   return 0;
	}
   
 }
  
}

void moveToGraveyard(char piece){
  int i,j;
  takenPiece = piece;
  if(piece >= 7 && piece <= 12){
    for(i = 0; i <= 1; i++) {
      for(j = 0; j < 8; j++){
        if(teststate[j][i] == '\0'){
          teststate[j][i] = piece;
  		  goodMove[7] = (char)j;
  		  goodMove[8] = (char)i;
          return;
        }
      }
    }
  }else if(piece >= 1 && piece <= 6){
      for(i =10; i<= 11; i++){
        for(j = 0; j < 8; j++){
          if(teststate[j][i] == '\0'){
            teststate[j][i] = piece;
            goodMove[7] = (char)j;
  		  	goodMove[8] = (char)i;
            return;
          }
        }
      }
    }else{
      return 1;
    }
}

void castlingMaintenance(){
  if(state[0][2] != WROOK && !leftRookWMovedOnce){ leftRookWMovedOnce = 1;}
  if(state[0][9] != WROOK && !rightRookWMovedOnce){ rightRookWMovedOnce = 1;}
  if(state[7][2] != BROOK && !leftRookBMovedOnce){ leftRookBMovedOnce = 1;}
  if(state[7][9] != BROOK && !rightRookBMovedOnce){ rightRookBMovedOnce = 1;}
  if(state[7][6] != BKING && (kingBMovedOnce != 0)){ kingBMovedOnce = 1;}
  if(state[0][6] != WKING && (kingWMovedOnce != 0)){kingWMovedOnce = 1;}
}

int isCheckForEnemy(){
  transition t;
  transition tonly;
  int k = 0; 
  int i,j,l,m;
  for(i = 0; i < 8 ; i++){
    for(j = 2; j <10; j++){
      if(teststate[i][j] == (char)(theircolor +6)){
        l = i;
        m = j;
        k = 1;
      }
      if(k == 1) break;
    }
    if(k == 1) break;
  }

  k = 0;
  for(i = 0; i < 8; i++){
    for(j = 2; j < 10; j++){
      if(teststate[i][j] > (char)(yourcolor) && teststate[i][j] <= (char)(yourcolor+5)){
        t.fromRow = i;
        t.fromCol = j;
        t.toRow = l;
        t.toCol = m;
        t.piece = teststate[i][j];
        testing = 1;
        int result = isLegal(t);
        if(result == 1){
          if(k == 0){
            tonly.fromRow =i; tonly.fromCol = j; tonly.toRow = l; tonly.toCol=m; tonly.piece = teststate[i][j];
          }
          printf("Piece that places oppoenent in check: %d \n", t.piece);
          k++;
        }
        testing = 0;
      }
    }
  }

  if(k == 0){
    return 0;
  }else if(k == 1){
    if(isCheckMate(tonly) == 1){
        return 2;
    }
    return 1;
  }else if(k > 1){
    t.piece = 13;
    if(isCheckMate(t) == 1){
      return 2;
    }
    return 1;
  }

  return 0;
}

int isCheckForYou(){
  transition t;
  int k = 0; 
  int i,j,l,m;
  for(i = 0; i < 8 ; i++){
    for(j = 2; j <10; j++){
      if(teststate[i][j] == (char)(yourcolor +6)){
        l = i;
        m = j;
        k = 1;
      }
      if(k == 1) break;
    }
    if(k == 1) break;
  }

  k = 0;
  for(i = 0; i < 8; i++){
    for(j = 2; j < 10; j++){
      if(teststate[i][j] > (char)(theircolor) && teststate[i][j] <= (char)(theircolor+5)){
        t.fromRow = i;
        t.fromCol = j;
        t.toRow = l;
        t.toCol = m;
        t.piece = teststate[i][j];
        testing = 1;
        if(isLegal(t)){
          k++;
        }
        testing = 0;
      }
    }
  }

  if(k <= 0){
    printf("%s", "\nThis move will not place you in check\n\n");
    return 0;
  }else{
    printf("%s", "\nThis move will place you in check. Try again\n\n");
    return 1;
  }
}


int isCheckMate(transition t){
  if(t.piece == 13){
    testing = 1;
    if(checkKingSurrounding(t) == 0) return 1;
    testing = 0;
    return 1;
  }else{
    testing = 1;
    int kingSurrounding = checkKingSurrounding(t);
    int saveKing =  checkSaveKing(t);
    int blockKing =  checkBlockKing(t);
    testing = 0;
    if((kingSurrounding == 0) && (saveKing == 0) && (blockKing == 0)){  
      return 1;
    }
  }
  return 0;
}


int checkKingSurrounding(transition t){
  initTestState();
  int safeAroundKing = 1;
  transition tnew;
  transition ttest;
  tnew.piece = (char)(theircolor + 6);
  tnew.fromRow = t.toRow;
  tnew.fromCol = t.toCol;
  int i,j,l,m;

  for(i = -1; i < 2; i++){
    for(j = -1 ; j < 2; j++){
      if((i != 0) || (j != 0)){
        tnew.toRow = tnew.fromRow + i;
        tnew.toCol = tnew.fromCol + j;
        if(tnew.toRow >=  0 && tnew.toRow < 7 && tnew.toCol >= 2 && tnew.toCol < 10){
          initTestState();
          if(isLegal(tnew)){
          takenPiece = teststate[tnew.toRow][tnew.toCol];
          teststate[tnew.toRow][tnew.toCol] = (char) (theircolor+6);
          teststate[tnew.fromRow][tnew.fromCol] = EMPTY;
          for(l = 0; l < 8; l++){
           for(m = 2; m < 10; m++){
              if(teststate[l][m] > (char)(yourcolor) && teststate[l][m] <= (char)(yourcolor+5)){
                ttest.fromRow = l;
                ttest.fromCol = m;
                ttest.toRow = tnew.toRow;
                ttest.toCol = tnew.toCol;
                ttest.piece = state[l][m];
                if(isLegal(ttest)){
                    safeAroundKing = 0;
                  }
                }
              }
            }
            if(safeAroundKing == 1){
              printf("\nKing can be moved to prevent its death\n");
              return 1;
            }

            restoreMove(tnew);
          }
        }
      }
    }
  }

  printf("\nKing cannot be moved to prevent its death\n");
  return 0;
}

int checkBlockKing(transition t){
  initTestState();
  int blockable = 0;
  int i, j,k;
  transition tnew;
    if(t.piece == WQUEEN || t.piece == BQUEEN){
      if(t.fromRow == t.toRow || t.fromCol == t.toCol){
        if(yourcolor == WHITE) t.piece = WROOK;
        else{t.piece = BROOK;}
      }
      else{
        if(yourcolor == WHITE) t.piece = WBISHOP;
        else{t.piece = BBISHOP;}
      }
    }
    if(t.piece == BROOK || t.piece == WROOK){
      if(t.toRow > t.fromRow){
        for(i = t.fromRow+1; i< t.toRow; i++){
          for(j = 0; j < 8; j++){
            for(k = 2; k < 10; k++){
              if(teststate[j][k] > (char)(theircolor) && teststate[j][k] <= (char)(theircolor+5)){
                tnew.fromRow = j;
                tnew.fromCol = k;
                tnew.toRow = i;
                tnew.toCol = t.fromCol;
                tnew.piece = teststate[j][k];
                if(isLegal(tnew)){
                  printf("%s\n", "\nThe path of the threatening piece can be blocked\n" );
                  blockable = 1;
                  return blockable;
                }
              }
            }
          }
        }
      }else if(t.toRow < t.fromRow){
        for(i = t.fromRow-1; i> t.toRow; i--){
          for(j = 0; j < 8; j++){
            for(k = 2; k < 10; k++){
              if(teststate[j][k] > (char)(theircolor) && teststate[j][k] <= (char)(theircolor+5)){
                tnew.fromRow = j;
                tnew.fromCol = k;
                tnew.toRow = i;
                tnew.toCol = t.fromCol;
                tnew.piece = teststate[j][k];
                if(isLegal(tnew)){
                  printf("%s\n", "\nThe path of the threatening piece can be blocked\n" );
                  blockable = 1;
                  return blockable;
                }
              }
            }
          }
        }
      }else if(t.toCol > t.fromCol){
        for(i = t.fromCol+1; i< t.toCol; i++){
          for(j = 0; j < 8; j++){
            for(k = 2; k < 10; k++){
              if(teststate[j][k] > (char)(theircolor) && teststate[j][k] <= (char)(theircolor+5)){
                tnew.fromRow = j;
                tnew.fromCol = k;
                tnew.toRow = t.fromRow;
                tnew.toCol = i;
                tnew.piece = teststate[j][k];
                if(isLegal(tnew)){
                  printf("%s\n", "\nThe path of the threatening piece can be blocked\n" );
                  blockable = 1;
                  return blockable;
                }
              }
            }
          }
        }
      }else if(t.toCol < t.fromCol){
        for(i = t.fromCol-1; i> t.toCol; i--){
          for(j = 0; j < 8; j++){
            for(k = 2; k < 10; k++){
              if(teststate[j][k] > (char)(theircolor) && teststate[j][k] <= (char)(theircolor+5)){
                tnew.fromRow = j;
                tnew.fromCol = k;
                tnew.toRow = t.fromRow;
                tnew.toCol = i;
                tnew.piece = teststate[j][k];
                if(isLegal(tnew)){
                  printf("%s\n", "\nThe path of the threatening piece can be blocked\n" );
                  blockable = 1;
                  return blockable;
                }
              }
            }
          }
        }
      }else{
      	printf("HI\n");
        return blockable;
      } 
    }
    else if(t.piece == BBISHOP || t.piece == WBISHOP){
      if(t.toRow < t.fromRow){
        if(t.toCol > t.fromCol){
          for(i = 1; i < t.toCol- t.fromCol; i++){
            for(j = 0; j < 8; j++){
              for(k = 2; k < 10; k++){
                if(teststate[j][k] > (char)(theircolor) && teststate[j][k] <= (char)(theircolor+5)){
                  tnew.fromRow = j;
                  tnew.fromCol = k;
                  tnew.toRow = t.fromRow-i;
                  tnew.toCol = t.fromCol+i;
                  tnew.piece = teststate[j][k];
                  if(isLegal(tnew)){
                    printf("%s\n", "\nThe path of the threatening piece can be blocked\n" );
                    blockable = 1;
                    return blockable;
                  }
                }
              }
            }
          }
        }else if(t.toCol < t.fromCol){
          for(i = 1; i < t.fromCol- t.toCol; i++){
            for(j = 0; j < 8; j++){
              for(k = 2; k < 10; k++){
                if(teststate[j][k] > (char)(theircolor) && teststate[j][k] <= (char)(theircolor+5)){
                  tnew.fromRow = j;
                  tnew.fromCol = k;
                  tnew.toRow = t.fromRow-i;
                  tnew.toCol = t.fromCol-i;
                  tnew.piece = teststate[j][k];
                  if(isLegal(tnew)){
                    printf("%s\n", "\nThe path of the threatening piece can be blocked\n" );
                    blockable = 1;
                    return blockable;
                  }
                }
              }
            }
          }
        }else{
          return blockable;
        }
      }else if(t.toRow > t.fromRow){
        if(t.toCol > t.fromCol){
          for(i = 1; i < t.toCol- t.fromCol; i++){
            for(j = 0; j < 8; j++){
              for(k = 2; k < 10; k++){
                if(teststate[j][k] > (char)(theircolor) && teststate[j][k] <= (char)(theircolor+5)){
                  tnew.fromRow = j;
                  tnew.fromCol = k;
                  tnew.toRow = t.fromRow+i;
                  tnew.toCol = t.fromCol+i;
                  tnew.piece = teststate[j][k];
                  if(isLegal(tnew)){
                    printf("%s\n", "\nThe path of the threatening piece can be blocked\n" );
                    blockable = 1;
                    return blockable;
                  }
                }
              }
            }
          }
        }else if(t.toCol < t.fromCol){
          for(i = 1; i < t.fromCol- t.toCol; i++){
            for(j = 0; j < 8; j++){
              for(k = 2; k < 10; k++){
                if(teststate[j][k] > (char)(theircolor) && teststate[j][k] <= (char)(theircolor+5)){
                  tnew.fromRow = j;
                  tnew.fromCol = k;
                  tnew.toRow = t.fromRow+i;
                  tnew.toCol = t.fromCol-i;
                  tnew.piece = teststate[j][k];
                  printf("GO HOME\n\n");
                  if(isLegal(tnew)){
                    printf("%s\n", "\nThe path of the threatening piece can be blocked\n" );
                    blockable = 1;
                    return blockable;
                  }
                }
              }
            }
          }
        }
        printf("%s\n", "\nThe path of the threatening piece cannot be blocked\n" );
        return 0;
      }
      else{
          printf("%s\n", "\nThe path of the threatening piece cannot be blocked\n" );
          return 0;
        }
    }else{
      printf("%s\n", "\nThe path of the threatening piece cannot be blocked\n" );
      return 0;
    }
}

int checkSaveKing(transition t){
  initTestState();
  int saveable = 0;
  int i, j;
  transition tnew;
  tnew.toRow = t.fromRow;
  tnew.toCol = t.fromCol;

    for(i = 0; i < 8; i++){
      for(j = 2; j < 10; j++){
        if(teststate[i][j] > (char)(theircolor) && teststate[i][j] <= (char)(theircolor+6)){
          tnew.fromRow = i;
          tnew.fromCol = j;
          tnew.piece = teststate[i][j];
          if(isLegal(tnew)){
            saveable = 1;
            printf("\nA piece can kill the piece putting opponent in check\n");
            return saveable;
          }
        }
      }
    }
    printf("\nA piece cannot kill the piece putting opponent in check\n");
    return saveable;
}


void restoreMove(transition t){
  int i,j;
  if(teststate[t.toRow][t.toCol] == t.piece){
    if(takenPiece != '\0'){
      teststate[t.toRow][t.toCol] = takenPiece;
    }else{
      teststate[t.toRow][t.toCol] = EMPTY;
    }
    teststate[t.fromRow][t.fromCol] = t.piece;
  }
}
