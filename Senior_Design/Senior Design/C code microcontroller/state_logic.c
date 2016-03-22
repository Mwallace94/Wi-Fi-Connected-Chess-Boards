#include <stdlib.h>
#include <stdio.h>

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

#define BLACK 6
#define WHITE 0

typedef struct{
  char piece;
  int fromRow;
  int fromCol;
  int toRow;
  int toCol;
} transition;

int yourcolor;
char** state[BROWS][BCOLS];
char** nextstate[BROWS][BCOLS];
int * enpassantB;
int * enpassantW;
int * kingBMovedOnce = 0;
int * kingWMovedOnce = 0;
int * leftRookBMovedOnce = 0;
int * leftRookWMovedOnce = 0;
int * rightRookBMovedOnce = 0;
int * rightRookWMovedOnce = 0;
int * castleConfirmed;
void initStartState();
void printState();
void printStateNoGrave();
void printNextStateNoGrave();
void zeroState();
void initStartNextState();
transition compareStates();
int isLegal(transition t);
void moveToGraveyard(char piece);
void castlingMaintenance();

int moverightcolor(int piece);
void playturn();

int main(int argc, char* argv[]) {
  yourcolor = WHITE;
  initStartState();
  initStartNextState();
  printState();

  //used to test moves with transitions
  playturn();

  //used to test a difference between states
  /*
    transition t = compareStates();
    printStateNoGrave();
    printf("\n");
    printNextStateNoGrave();
    printf("%d, %d, %d, %d, %d \n", (int) t.piece, t.fromRow, t.fromCol, t.toRow, t.toCol);
    printf("is legal? : %d\n", isLegal(t));
  */
  //printState();

  return 1;
}

//allows user to play the game based on input
void playturn() {
  transition t;
  while(1) {
    int move = 0;
    while(!move) {
      printf("Input transistion:");
      if(scanf("%d %d %d %d %d", &t.piece, &t.fromRow, &t.fromCol, &t.toRow, &t.toCol) == EOF)  return;
      if(t.piece == 0) printStateNoGrave();
      move = isLegal(t);
      printf("\nIs the move legal?:%d\n\n", move);
    }
    if(move) {
      nextstate[t.fromRow][t.fromCol] = EMPTY;
      nextstate[t.toRow][t.toCol] = t.piece;
      if(enpassantW){
        nextstate[t.toRow-1][t.toCol] = EMPTY;
        enpassantW = 0;
      }else if(enpassantB){
        nextstate[t.toRow+1][t.toCol] = EMPTY;
        enpassantB = 0;
      }
      if(castleConfirmed){
        castlingAction(castleConfirmed);
		castleConfirmed = 0;
      }
      //printStateNoGrave();
	  printState();
      printf("\n");
      printNextStateNoGrave();
      state[t.fromRow][t.fromCol] = EMPTY;
      state[t.toRow][t.toCol] = t.piece;

      if(castleConfirmed){
        if(castleConfirmed == 1){
          state[0][2] = EMPTY;
          state[0][5] = WROOK;
        }else if(castleConfirmed == 2){
          state[0][9] = EMPTY;
          state[0][7] = WROOK;
        }else if(castleConfirmed == 3){
          state[7][2] = EMPTY;
          state[7][5] = BROOK;
        }else if(castleConfirmed == 4){
          state[7][9] = EMPTY;
          state[7][7] = BROOK;
        }
      }
      castlingMaintenance();
	//printf("%d %d", kingBMovedOnce, kingBMovedOnce == 0);
    }
    if(yourcolor == WHITE) yourcolor = BLACK;
    else if(yourcolor == BLACK) yourcolor = WHITE;

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

//initialize for nextstage, testng purposes
void initStartNextState() {
  //zeroState();
  int i;
  for(i = 2; i <= 9; i++) {
    nextstate[1][i] = WPAWN;
    nextstate[6][i] = BPAWN;
  }
  nextstate[0][2] = WROOK;
  nextstate[0][3] = WKNIGHT;
  nextstate[0][4] = WBISHOP;
  nextstate[0][5] = WQUEEN;
  nextstate[0][6] = WKING;
  nextstate[0][7] = WBISHOP;
  nextstate[0][8] = WKNIGHT;
  nextstate[0][9] = WROOK;

  nextstate[7][2] = BROOK;
  nextstate[7][3] = BKNIGHT;
  nextstate[7][4] = BBISHOP;
  nextstate[7][5] = BQUEEN;
  nextstate[7][6] = BKING;
  nextstate[7][7] = BBISHOP;
  nextstate[7][8] = BKNIGHT;
  nextstate[7][9] = BROOK;
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

//prints for nextstate, test
void printNextStateNoGrave() {
  int i, j;
  for(i = 0; i < BROWS; i++) {
    for(j = 2; j < BCOLS-2; j++) {
      printf("%d\t", (int) nextstate[i][j]);
    }
    printf("\n");
  }
}

//compares states difference, testing
//returns an array of size 12; sectioned by 6. from piece row col, to piece row col. allows for 2 total pieces to move.
transition compareStates() {
  int i, j;
  transition t;
  for(i = 0; i < BROWS; i++) {
    for(j = 0; j < BCOLS; j++) {
      if (state[i][j] != nextstate[i][j] && state[i][j] != 0) {
        printf("piece %d moved from: %d, %d \n", (int) state[i][j], i, j);
        t.piece = state[i][j];
        t.fromRow = i;
        t.fromCol = j;
      }
      if (state[i][j] != nextstate[i][j] && nextstate[i][j] != 0) {
        printf("piece %d moved to: %d, %d \n", (int) nextstate[i][j], i, j);
        t.toRow = i;
        t.toCol = j;
      }
    }
  }
  return t;
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
  return 0;
}

//detects if current move is legal
int isLegal(transition t) {
  int ydis = abs(t.fromRow - t.toRow); //ydistance
  int xdis = abs(t.fromCol - t.toCol);//x distance
  int dis = ydis + xdis;//x +y

  if(!moverightcolor(t.piece)) return 0;
  //only important for which color you are, but this is ambiguous at the time. AKA will black and white be always on same side or user disgression.
  //will create both directions I suppose, but will be white towards player and black away for not
  if(t.piece == WPAWN) {
    int ydist = t.toRow - t.fromRow;
    int xdist = t.toCol - t.fromCol;
    //should always be true for move only
    if(ydist == 1 && !xdis && (state[t.toRow][t.toCol] == '\0')) return 1;
    else if(t.fromRow == 1 && ydist == 2 && (state[t.toRow][t.toCol] == '\0') && (state[t.toRow-1][t.toCol] == '\0')) return 1;
    //taking a piece
    else if(ydist == 1 && abs(xdist) == 1 && (state[t.toRow][t.toCol] != '\0')) {
      if(state[t.toRow][t.toCol] >= 1 && state[t.toRow][t.toCol] <= 6){
        //move piece pawn takes to graveyard
        moveToGraveyard(state[t.toRow][t.toCol]);
        return 1;
      }
	  return 0;
	}
	//enpassant
      else if(abs(ydist) == 1 && abs(xdist) == 1 && state[t.toRow-1][t.toCol] == 1 && (t.toRow-1 == 4)){
        moveToGraveyard(state[t.toRow-1][t.toCol]);
        nextstate[t.toRow-1][t.toCol] = EMPTY;
        enpassantW =1;
        return 1;
	}
    else{
		return 0;
	}
  }
 if(t.piece == BPAWN) {
   int ydist = t.fromRow - t.toRow;
   int xdist = t.toCol - t.fromCol;
   //should always be true for move only
   if(ydist == 1 && !xdis && (state[t.toRow][t.toCol] == '\0')) return 1;
   else if(t.fromRow == 6 && ydist == 2 && (state[t.toRow][t.toCol] == '\0') && (state[t.toRow+1][t.toCol] == '\0')) return 1;
   //add taking piece here

   else if(abs(ydist) == 1 && abs(xdist) == 1 && (state[t.toRow][t.toCol] != '\0')){
     if(state[t.toRow][t.toCol] >= 7 && state[t.toRow][t.toCol] <= 12){
       moveToGraveyard(state[t.toRow][t.toCol]);
       return 1;
     }
	 return 0;
   }
	 //enpassant
     else if(abs(ydist) == 1 && abs(xdist) == 1 && state[t.toRow+1][t.toCol] == WPAWN && (t.toRow+1 == 3)){
	   moveToGraveyard(state[t.toRow+1][t.toCol]);
       nextstate[t.toRow+1][t.toCol] = EMPTY;
       enpassantB = 1;
       return 1;
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
         if((i == t.toRow) && state[i][t.fromCol] != '\0'){
           if(t.piece == WROOK && state[i][t.fromCol] >= 1 && state[i][t.fromCol] <= 6){
             moveToGraveyard(state[i][t.fromCol]);
             return 1;
           }
           else if(t.piece == BROOK && state[i][t.fromCol] >= 7 && state[i][t.fromCol] <= 12){
				
             moveToGraveyard(state[i][t.fromCol]);
             return 1;
           }
           return 0;
         }
         else if((i == t.toRow) && state[i][t.fromCol] == '\0'){
           return 1;
         }

         if(state[i][t.fromCol] != '\0') return 0;
       }
     } else {
       if(t.fromRow == t.toRow) return 0;
       int i;
       for(i = t.fromRow-1; i >= t.toRow; i--) {
         if((i == t.toRow) && state[i][t.fromCol] != '\0'){
           if(t.piece == WROOK && state[t.toRow][t.toCol] >= 1 && state[t.toRow][t.toCol] <= 6){
			 moveToGraveyard(state[t.toRow][t.toCol]);
             return 1;
           }
           else if(t.piece == BROOK && state[t.toRow][t.toCol] >= 7 && state[t.toRow][t.toCol] <= 12){
			   printf("%d %d %d\n", t.toRow, t.toCol, state[t.toRow][t.toCol]);
             moveToGraveyard(state[t.toRow][t.toCol]);
             return 1;
           }
		   
           return 0;
         }
         else if((i == t.toRow) && state[t.toRow][t.fromCol] == '\0'){
           return 1;
         }

         if(state[i][t.fromCol] != '\0') {
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
         if((i == t.toCol) && state[t.fromRow][i] != '\0'){
           if(t.piece == WROOK && state[t.fromRow][i] >= 1 && state[t.fromRow][i] <=6){
             moveToGraveyard(state[t.fromRow][i]);
             return 1;
           }
           else if(t.piece == BROOK && state[t.fromRow][i] >= 7 && state[t.fromRow][i] <= 12){
             moveToGraveyard(state[t.fromRow][i]);
             return 1;
           }
           return 0;
         }
         else if((i == t.toCol) && state[t.fromRow][i] == '\0'){
           return 1;
         }

         if(state[t.fromRow][i] != '\0') return 0;
       }
     }
	  else {
       if(t.fromCol == t.toCol) return 0;
       int i;
       for(i = t.fromCol-1; i >= t.toCol; i--) {
         if((i == t.toCol) && state[t.fromRow][i] != '\0'){
           if(t.piece == WROOK && state[t.fromRow][i] >= 1 && state[t.fromRow][i] <= 6){
             moveToGraveyard(state[t.fromRow][t.toCol]);
             return 1;
           }
           else if(t.piece == BROOK && state[t.fromRow][i] >= 7 && state[t.fromRow][i] <= 12){
             moveToGraveyard(state[t.fromRow][t.toCol]);
             return 1;
           }
           return 0;
         }
         else if((i == t.toCol) && state[t.fromRow][t.toCol] == '\0'){
           return 1;
         }
         if(state[t.fromRow][t.toCol] != '\0') return 0;
       }
     }
   }
   //castling here
   return 1;
 }
//checks
 if(t.piece == WKNIGHT || t.piece == BKNIGHT) {
   //detects move only
   if(ydis && xdis && (dis == 3) && state[t.toRow][t.toCol] == '\0') {
     return 1;
   }else if(ydis && xdis && dis == 3 && state[t.toRow][t.toCol] != '\0'){
     if(state[t.toRow][t.toCol] >= 1 && state[t.toRow][t.toCol] <= 6 && t.piece == WKNIGHT){
       moveToGraveyard(state[t.toRow][t.toCol]);
       return 1;
     } else if(state[t.toRow][t.toCol] >= 7 && state[t.toRow][t.toCol] <= 12 && t.piece == BKNIGHT){
       moveToGraveyard(state[t.toRow][t.toCol]);
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
       if(state[t.fromRow+i][t.fromCol+i] != '\0' && (i != ydis)) return 0;
       else if(i == ydis){
         if(t.piece == BBISHOP && state[t.fromRow+i][t.fromCol+i] != '\0'&& state[t.fromRow+i][t.fromCol+i] >=7 && state[t.fromRow+i][t.fromCol+i] <= 12){
           moveToGraveyard(state[t.fromRow+i][t.fromCol+i]);
           return 1;
         }else if(t.piece == WBISHOP && state[t.fromRow+i][t.fromCol+i] != '\0'&& state[t.fromRow+i][t.fromCol+i] >=1 && state[t.fromRow+i][t.fromCol+i] <= 6){
           moveToGraveyard(state[t.fromRow+i][t.fromCol+i]);
           return 1;
         }else if((t.piece == WBISHOP || t.piece== BBISHOP) && state[t.fromRow+i][t.fromCol+i] == '\0'){
			 return 1;
		 }
		 else{
           return 0;
         }
       }
     }
 } else if(t.fromRow > t.toRow && t.fromCol < t.toCol) {
     for(i = 1; i <= ydis; i++) {
       if(state[t.fromRow-i][t.fromCol+i] != '\0' && (i != ydis)) return 0;
       else if(i == ydis){
         if(t.piece == BBISHOP && state[t.fromRow-i][t.fromCol+i] != '\0'&& state[t.fromRow-i][t.fromCol+i] >=7 && state[t.fromRow-i][t.fromCol+i] <= 12){
           moveToGraveyard(state[t.fromRow-i][t.toCol+i]);
           return 1;
         }else if(t.piece == WBISHOP && state[t.fromRow-i][t.fromCol+i] != '\0'&& state[t.fromRow-i][t.fromCol+i] >=1 && state[t.fromRow-i][t.fromCol+i] <= 6){
           moveToGraveyard(state[t.fromRow-i][t.fromCol+i]);
           return 1;
         }else if((t.piece == WBISHOP || t.piece== BBISHOP) && state[t.fromRow-i][t.fromCol+i] == '\0'){
			 return 1;
		 }else{
           return 0;
         }
       }
     }
 } else if(t.fromRow < t.toRow && t.fromCol > t.toCol) {
     for(i = 1; i <= ydis; i++) {
       if(state[t.fromRow+i][t.fromCol-i] != '\0' && (i != ydis)) return 0;
       else if(i == ydis){
         if(t.piece == BBISHOP && state[t.fromRow+i][t.fromCol-i] != '\0'&& state[t.fromRow+i][t.fromCol-i] >=7 && state[t.fromRow+i][t.fromCol-i] <= 12){
           moveToGraveyard(state[t.fromRow+i][t.fromCol-i]);
           return 1;
         }else if(t.piece == WBISHOP && state[t.fromRow+i][t.fromCol-i] != '\0'&& state[t.fromRow+i][t.fromCol-i] >=1 && state[t.fromRow+i][t.fromCol-i] <= 6){
           moveToGraveyard(state[t.fromRow+i][t.fromCol-i]);
           return 1;
         }else if((t.piece == WBISHOP || t.piece== BBISHOP) && state[t.fromRow+i][t.fromCol-i] == '\0'){
			 return 1;
		 }else{
           return 0;
         }
       }
     }
 } else if(t.fromRow > t.toRow && t.fromCol > t.toCol) {
     for(i = 1; i <= ydis; i++) {
       if(state[t.fromRow-i][t.fromCol-i] != '\0' && (i != ydis)) return 0;
       else if(i == ydis){
         if(t.piece == BBISHOP && state[t.fromRow-i][t.fromCol-i] != '\0'&& state[t.fromRow-i][t.fromCol-i] >=7 && state[t.fromRow-i][t.fromCol-i] <= 12){
           moveToGraveyard(state[t.fromRow-i][t.fromCol-i]);
           return 1;
         }else if(t.piece == WBISHOP && state[t.fromRow-i][t.fromCol-i] != '\0'&& state[t.fromRow-i][t.fromCol-i] >=1 && state[t.fromRow-i][t.fromCol-i] <= 6){
           moveToGraveyard(state[t.fromRow-i][t.fromCol-i]);
           return 1;
         }else if((t.piece == WBISHOP || t.piece== BBISHOP) && state[t.fromRow-i][t.fromCol-i] == '\0'){
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
   if((dis == 1 || (dis == 2 && (xdis && ydis))) && state[t.toRow][t.toCol] == '\0'){
	return 1;
   }
   else if((dis == 1  || (dis == 2 && (xdis && ydis)))&& state[t.toRow][t.toCol] != '\0'){
     if(t.piece == WKING && state[t.toRow][t.toCol] >= 1 && state[t.toRow][t.toCol] <= 6){
       moveToGraveyard(state[t.toRow][t.toCol]);
       return 1;
     }else if(t.piece == BKING && state[t.toRow][t.toCol] >= 7 && state[t.toRow][t.toCol] <= 12){
       moveToGraveyard(state[t.toRow][t.toCol]);
       return 1;
     }
	 
     return 0;
   }else if(dis == 2){ 
   //printf("%d %d\n", kingWMovedOnce == 0, t.piece == WKING);
     if((kingWMovedOnce == 0) && t.piece == WKING){
       if(!leftRookWMovedOnce && t.toCol < t.fromCol && (state[0][3] == '\0' && state[0][4] == '\0' && state[0][5] == '\0') && state[0][2] == WROOK){
         castleConfirmed = 1;
         return 1;
	   }else if(!rightRookWMovedOnce && (t.toCol > t.fromCol) && (state[0][7] == '\0' && state[0][8] == '\0') && state[0][9] == WROOK){
		castleConfirmed = 2;
         return 1;
       }
     }else if((kingBMovedOnce == 0) && t.piece == BKING){
       if(!leftRookBMovedOnce && t.toCol < t.fromCol && (state[7][3] == '\0' && state[7][4] == '\0' && state[7][5] == '\0') && state[7][2] == BROOK){
		 castleConfirmed = 3;
         return 1;
       }else if(!rightRookBMovedOnce && t.toCol > t.fromCol && (state[7][7] == '\0' && state[7][8] == '\0') && state[7][9] == WROOK){
         castleConfirmed = 4;
         return 1;
       }
     }else{
       return 0;
     }
   }
   
   else{
	   return 0;
	}
   
 }
  
}

void moveToGraveyard(char piece){
	printf("PIECE BEING MOVED %d\n\n\n\n", piece);
  int i,j;
  if(piece >= 7 && piece <= 12){
    for(i = 0; i <= 1; i++) {
      for(j = 0; j < 8; j++){
        if(state[j][i] == '\0'){
          state[j][i] = piece;
          return;
        }
      }
    }
  }else if(piece >= 1 && piece <= 6){
      for(i =10; i<= 11; i++){
        for(j = 0; j < 8; j++){
          if(state[j][i] == '\0'){
            state[j][i] = piece;
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

void castlingAction(int caseNumber){
  if(!caseNumber || caseNumber > 4){
    exit(-1);
  }else{
	 if(caseNumber == 1){
      nextstate[0][2] = EMPTY;
      nextstate[0][5] = WROOK;
    }else if(caseNumber ==2){
      nextstate[0][9] = EMPTY;
      nextstate[0][7] = WROOK;
    }else if(caseNumber ==3){
      nextstate[7][2] = EMPTY;
      nextstate[7][5] = BROOK;
    }else {
      nextstate[7][9] = EMPTY;
      nextstate[7][7] = BROOK;
    }
  }
}
    //below perhaps used to detect piece collision
    //verticalCollision();
    //horizontalCollision();

    // if enemy piece is moved to the graveyard detect move and make sure next piece takes that piece and is legel.
    // Keep old state, but create flag with position taken to make sure your piece takes theres
    // int partialMove(transition) {

    // }








