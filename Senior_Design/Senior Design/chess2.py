from graphics import *
import subprocess
import socket

PORT = 666
SERVER = '192.168.173.1'

BPAWN = 1
BROOK = 2
BKNIGHT = 3
BBISHOP = 4
BQUEEN = 5
BKING = 6

WPAWN = 7
WROOK = 8
WKNIGHT = 9
WBISHOP = 10
WQUEEN = 11
WKING = 12

SQUARE_SZ = 50
SQ_SZ_HALF = 25

CONNECT_BTN_TOPL_X = 50
CONNECT_BTN_TOPL_Y = 425
CONNECT_BTN_BOTR_X = 150
CONNECT_BTN_BOTR_Y = 475

READY_BTN_TOPL_X = 160
READY_BTN_TOPL_Y = 425
READY_BTN_BOTR_X = 260
READY_BTN_BOTR_Y = 475

DISPLAY_BOX_TOPL_X = 270
DISPLAY_BOX_TOPL_Y = 425
DISPLAY_BOX_BOTR_X = 470
DISPLAY_BOX_BOTR_Y = 475

END_BTN_TOPL_X = 480
END_BTN_TOPL_Y = 425
END_BTN_BOTR_X = 540
END_BTN_BOTR_Y = 475

def setup_graphics():

    win = GraphWin('Chess', 600, 500) # give title and dimensions
    squares = [[0 for x in range(8)] for y in range(12)]

    for x in range(0, 12):
        for y in range(0,8):
            squares[x][y] = Rectangle(Point(x * SQUARE_SZ, y * SQUARE_SZ), Point(x*SQUARE_SZ + SQUARE_SZ, y*SQUARE_SZ + SQUARE_SZ))
            if x < 2 or x > 9:
                squares[x][y].setFill("linen")
            elif (x + y) % 2 == 0:
                squares[x][y].setFill("gray")
            else: 
                squares[x][y].setFill("white")
            squares[x][y].draw(win)

    b1 = Rectangle(Point(CONNECT_BTN_TOPL_X, CONNECT_BTN_TOPL_Y), Point(CONNECT_BTN_BOTR_X, CONNECT_BTN_BOTR_Y))
    b2 = Rectangle(Point(READY_BTN_TOPL_X, READY_BTN_TOPL_Y), Point(READY_BTN_BOTR_X, READY_BTN_BOTR_Y))
    b3 = Rectangle(Point(DISPLAY_BOX_TOPL_X, DISPLAY_BOX_TOPL_Y), Point(DISPLAY_BOX_BOTR_X, DISPLAY_BOX_BOTR_Y))
    b5 = Rectangle(Point(END_BTN_TOPL_X, END_BTN_TOPL_Y), Point(END_BTN_BOTR_X, END_BTN_BOTR_Y))

    b1.setFill("grey")
    b2.setFill("grey")
    b3.setFill("white")
    b5.setFill("grey")

    b1.draw(win)
    b2.draw(win)
    b3.draw(win)
    b5.draw(win)

    t1 = Text(Point((CONNECT_BTN_TOPL_X + CONNECT_BTN_BOTR_X) / 2, (CONNECT_BTN_TOPL_Y + CONNECT_BTN_BOTR_Y) / 2), "CONNECT")
    t2 = Text(Point((READY_BTN_TOPL_X + READY_BTN_BOTR_X) / 2, (READY_BTN_TOPL_Y + READY_BTN_BOTR_Y) / 2), "READY")
    t5 = Text(Point((END_BTN_TOPL_X + END_BTN_BOTR_X) / 2, (END_BTN_TOPL_Y + END_BTN_BOTR_Y) / 2), "EXIT")

    t1.draw(win)
    t2.draw(win)
    t5.draw(win)

    return (win, squares)

def setup_connection():

    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((SERVER, PORT))
    return sock

def setup_board(win, squares):

#white pieces

    pieces = [[0 for x in range(8)] for y in range(12)]

    for x in range(0, 12):
        for y in range(0,8):
            pieces[x][y] = (0, 0)

    pieces[2][0] = (Text(Point(125, (SQ_SZ_HALF)), '♖'), WROOK)
    pieces[2][0][0].setSize((SQ_SZ_HALF))
    pieces[2][0][0].draw(win) 

    pieces[3][0] = (Text(Point(175, (SQ_SZ_HALF)), '♘'), WKNIGHT)
    pieces[3][0][0].setSize((SQ_SZ_HALF))
    pieces[3][0][0].draw(win) 

    pieces[4][0] = (Text(Point(225, (SQ_SZ_HALF)), '♗'), WBISHOP)
    pieces[4][0][0].setSize((SQ_SZ_HALF))
    pieces[4][0][0].draw(win) 

    pieces[5][0] = (Text(Point(275, (SQ_SZ_HALF)), '♕'), WQUEEN)
    pieces[5][0][0].setSize((SQ_SZ_HALF))
    pieces[5][0][0].draw(win) 

    pieces[6][0] = (Text(Point(325, (SQ_SZ_HALF)), '♔'), WKING)
    pieces[6][0][0].setSize((SQ_SZ_HALF))
    pieces[6][0][0].draw(win) 

    pieces[7][0] = (Text(Point(375, (SQ_SZ_HALF)), '♗'), WBISHOP)
    pieces[7][0][0].setSize((SQ_SZ_HALF))
    pieces[7][0][0].draw(win) 

    pieces[8][0] = (Text(Point(425, (SQ_SZ_HALF)), '♘'), WKNIGHT)
    pieces[8][0][0].setSize((SQ_SZ_HALF))
    pieces[8][0][0].draw(win) 

    pieces[9][0] = (Text(Point(475, (SQ_SZ_HALF)), '♖'), WROOK)
    pieces[9][0][0].setSize((SQ_SZ_HALF))
    pieces[9][0][0].draw(win) 
    
    for x in range(2, 10):
        pieces[x][1] = (Text(Point(x*SQUARE_SZ + (SQ_SZ_HALF), 75), '♙'), WPAWN)
        pieces[x][1][0].setSize((SQ_SZ_HALF))
        pieces[x][1][0].draw(win) 

#black pieces

    pieces[2][7] = (Text(Point(125, 375), '♜'), BROOK)
    pieces[2][7][0].setSize((SQ_SZ_HALF))
    pieces[2][7][0].draw(win) 

    pieces[3][7] = (Text(Point(175, 375), '♞'), BKNIGHT)
    pieces[3][7][0].setSize((SQ_SZ_HALF))
    pieces[3][7][0].draw(win) 

    pieces[4][7] = (Text(Point(225, 375), '♝'), BBISHOP)
    pieces[4][7][0].setSize((SQ_SZ_HALF))
    pieces[4][7][0].draw(win) 

    pieces[5][7] = (Text(Point(275, 375), '♛'), BQUEEN)
    pieces[5][7][0].setSize((SQ_SZ_HALF))
    pieces[5][7][0].draw(win) 

    pieces[6][7] = (Text(Point(325, 375), '♚'), BKING)
    pieces[6][7][0].setSize((SQ_SZ_HALF))
    pieces[6][7][0].draw(win) 

    pieces[7][7] = (Text(Point(375, 375), '♝'), BBISHOP)
    pieces[7][7][0].setSize((SQ_SZ_HALF))
    pieces[7][7][0].draw(win) 

    pieces[8][7] = (Text(Point(425, 375), '♞'), BKNIGHT)
    pieces[8][7][0].setSize((SQ_SZ_HALF))
    pieces[8][7][0].draw(win) 

    pieces[9][7] = (Text(Point(475, 375), '♜'), BROOK)
    pieces[9][7][0].setSize((SQ_SZ_HALF))
    pieces[9][7][0].draw(win) 
    
    for x in range(2, 10):
        pieces[x][6] = (Text(Point(x*SQUARE_SZ + (SQ_SZ_HALF), 325), '♟'), BPAWN)
        pieces[x][6][0].setSize((SQ_SZ_HALF))
        pieces[x][6][0].draw(win)  

    # movepiece(win, pieces, (1, 2, 1, 2, 3))
    # movepiece(win, pieces, (1, 2, 6, 2, 4))
    # movepiece(win, pieces, (1, 2, 0, 2, 2))
    # movepiece(win, pieces, (1, 2, 7, 2, 5))
    # movepiece(win, pieces, (1, 2, 2, 3, 2))
    # movepiece(win, pieces, (1, 2, 5, 3, 5))

    return pieces

def movepiece(win, pieces, movement):

    # value = ''
    # for x in range(0,8):
    #     for y in range(0,12):
    #         value += 'str(pieces[' + str(y) + '][' + str(x) + '][1]), '
    value = subprocess.call(['./legal.exe', str(movement[0]), str(movement[1]), str(movement[2]), str(movement[3]), str(movement[4]), str(pieces[0][0][1]), str(pieces[1][0][1]), str(pieces[2][0][1]), str(pieces[3][0][1]), str(pieces[4][0][1]), str(pieces[5][0][1]), str(pieces[6][0][1]), str(pieces[7][0][1]), str(pieces[8][0][1]), str(pieces[9][0][1]), str(pieces[10][0][1]), str(pieces[11][0][1]), str(pieces[0][1][1]), str(pieces[1][1][1]), str(pieces[2][1][1]), str(pieces[3][1][1]), str(pieces[4][1][1]), str(pieces[5][1][1]), str(pieces[6][1][1]), str(pieces[7][1][1]), str(pieces[8][1][1]), str(pieces[9][1][1]), str(pieces[10][1][1]), str(pieces[11][1][1]), str(pieces[0][2][1]), str(pieces[1][2][1]), str(pieces[2][2][1]), str(pieces[3][2][1]), str(pieces[4][2][1]), str(pieces[5][2][1]), str(pieces[6][2][1]), str(pieces[7][2][1]), str(pieces[8][2][1]), str(pieces[9][2][1]), str(pieces[10][2][1]), str(pieces[11][2][1]), str(pieces[0][3][1]), str(pieces[1][3][1]), str(pieces[2][3][1]), str(pieces[3][3][1]), str(pieces[4][3][1]), str(pieces[5][3][1]), str(pieces[6][3][1]), str(pieces[7][3][1]), str(pieces[8][3][1]), str(pieces[9][3][1]), str(pieces[10][3][1]), str(pieces[11][3][1]), str(pieces[0][4][1]), str(pieces[1][4][1]), str(pieces[2][4][1]), str(pieces[3][4][1]), str(pieces[4][4][1]), str(pieces[5][4][1]), str(pieces[6][4][1]), str(pieces[7][4][1]), str(pieces[8][4][1]), str(pieces[9][4][1]), str(pieces[10][4][1]), str(pieces[11][4][1]), str(pieces[0][5][1]), str(pieces[1][5][1]), str(pieces[2][5][1]), str(pieces[3][5][1]), str(pieces[4][5][1]), str(pieces[5][5][1]), str(pieces[6][5][1]), str(pieces[7][5][1]), str(pieces[8][5][1]), str(pieces[9][5][1]), str(pieces[10][5][1]), str(pieces[11][5][1]), str(pieces[0][6][1]), str(pieces[1][6][1]), str(pieces[2][6][1]), str(pieces[3][6][1]), str(pieces[4][6][1]), str(pieces[5][6][1]), str(pieces[6][6][1]), str(pieces[7][6][1]), str(pieces[8][6][1]), str(pieces[9][6][1]), str(pieces[10][6][1]), str(pieces[11][6][1]), str(pieces[0][7][1]), str(pieces[1][7][1]), str(pieces[2][7][1]), str(pieces[3][7][1]), str(pieces[4][7][1]), str(pieces[5][7][1]), str(pieces[6][7][1]), str(pieces[7][7][1]), str(pieces[8][7][1]), str(pieces[9][7][1]), str(pieces[10][7][1]), str(pieces[11][7][1])])
    #print(value)

    temp = 0

    rowdis = movement[3] - movement[1]
    coldis = movement[4] - movement[2]
    pieces[movement[1]][movement[2]][0].move(rowdis * SQUARE_SZ, coldis * SQUARE_SZ)

    #move piece to graveyard
    if pieces[movement[3]][movement[4]] != (0, 0):
        if pieces[movement[3]][movement[4]][1] >= 1 and pieces[movement[3]][movement[4]][1] <= 6:
            for x in range(0, 2):
                if temp == 1:
                    break
                for y in range(0, 8):
                    if pieces[x][y] == (0, 0):
                        pieces[movement[3]][movement[4]][0].move(SQUARE_SZ * (x - movement[3]), SQUARE_SZ * (y - movement[4]))
                        pieces[x][y] = pieces[movement[3]][movement[4]]
                        temp = 1
                        break
        if pieces[movement[3]][movement[4]][1] >= 7 and pieces[movement[3]][movement[4]][1] <= 12:
            for x in range(10, 12):
                if temp == 1:
                    break
                for y in range(0, 8):
                    if pieces[x][y] == (0, 0):
                        pieces[movement[3]][movement[4]][0].move(SQUARE_SZ * (x - movement[3]), SQUARE_SZ * (y - movement[4]))
                        pieces[x][y] = pieces[movement[3]][movement[4]]
                        temp = 1
                        break        

    pieces[movement[3]][movement[4]] = pieces[movement[1]][movement[2]]
    pieces[movement[1]][movement[2]] = (0, 0)

def concat(i):
    return b' ' + str(i).encode()

def main():

    sock = setup_connection()
    sock.sendto(b'.connect', (SERVER, PORT))
    (win, squares) = setup_graphics()
    pieces = setup_board(win, squares)
    
    while 1:

        

        #used to only be able to click on a piece in play
        temp = (0, 0)
        while temp == (0, 0):
            point = win.getMouse()
            fromrow = point.x // SQUARE_SZ
            fromcol = point.y // SQUARE_SZ
            
            if(point.y <= 400):
                temp = pieces[fromrow][fromcol]
                
            if fromrow == 0 or fromrow == 1 or fromrow == 10 or fromrow == 11:
                temp = (0, 0)
                
            if(point.x >= CONNECT_BTN_TOPL_X and point.x <= CONNECT_BTN_BOTR_X and point.y >= CONNECT_BTN_TOPL_Y and point.y <= CONNECT_BTN_BOTR_Y):
                sock = setup_connection()
                sock.sendto(b'.connect', (SERVER, PORT))
                displaytext = str(sock.recv(1024), "utf-8")
                print(displaytext)
                t3 = Text(Point(370, 450), displaytext)
                t3.draw(win)
                
            if(point.x >= READY_BTN_TOPL_X and point.x <= READY_BTN_BOTR_X and point.y >= READY_BTN_TOPL_Y and point.y <= READY_BTN_BOTR_Y):
                sock = setup_connection()
                sock.sendto(b'.ready', (SERVER, PORT))
                displaytext = str(sock.recv(1024), "utf-8")
                print(displaytext)
                t3 = Text(Point(370, 450), displaytext)
                t3.draw(win)
                
            if(point.x >= END_BTN_TOPL_X and point.x <= END_BTN_BOTR_X and point.y >= END_BTN_TOPL_Y and point.y <= END_BTN_BOTR_Y):
                sock = setup_connection()
                sock.sendto(b'.end', (SERVER, PORT))
                return    
        
        squares[fromrow][fromcol].setFill("lime")
        point = win.getMouse()
        torow = point.x // SQUARE_SZ
        tocol = point.y // SQUARE_SZ
        if fromrow < 2 or fromrow > 9:
            squares[fromrow][fromcol].setFill("linen")
        elif (fromrow + fromcol) % 2 == 0:
            squares[fromrow][fromcol].setFill("gray")
        else: 
            squares[fromrow][fromcol].setFill("white")

        #movement = (piece-to-move, ...)
        movement = (pieces[fromrow][fromcol][1], fromrow, fromcol, torow, tocol)
        movepiece(win, pieces, movement)
        print(movement)

        sock = setup_connection()
        # mixup during, microcontroller code asks for rows before cols.
        msg = b'.move' + concat(movement[0]) + concat(movement[2]) + concat(movement[1]) + concat(movement[4]) + concat(movement[3])
        sock.sendto(msg, (SERVER, PORT))

        displaytext = str(sock.recv(1024), "utf-8")
        print(displaytext)
        t3 = Text(Point(370, 450), displaytext)
        t3.draw(win)


main()
