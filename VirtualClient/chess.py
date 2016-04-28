from graphics import *
import subprocess
import socket
import time

PORT = 666
SERVER = '192.168.173.1'

BLACK = 0
WHITE = 6

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

# If you change SQUARE_SZ, don't forget to change SQ_SZ_HALF!
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

# TODO: Add "Reset" button (no need for smooth movement, just setup_board()).

#States
NOTCONNECTED = 0
CONNECTED = 1
READY = 2
WAITING = 3
MOVING = 4

#############################################
# Functions for setup                       #
#############################################

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

    # Test movepiece function
    # movepiece(win, pieces, (1, 2, 1, 2, 3))
    # movepiece(win, pieces, (1, 2, 6, 2, 4))
    # movepiece(win, pieces, (1, 2, 0, 2, 2))
    # movepiece(win, pieces, (1, 2, 7, 2, 5))
    # movepiece(win, pieces, (1, 2, 2, 3, 2))
    # movepiece(win, pieces, (1, 2, 5, 3, 5))

    return (win, squares, pieces)

#############################################
# Functions for moving pieces               #
#############################################

def movepiece(pieces, movement):

    temp = 0

    rowdis = movement[3] - movement[1]
    coldis = movement[4] - movement[2]
    #pieces[movement[1]][movement[2]][0].move(rowdis * SQUARE_SZ, coldis * SQUARE_SZ)

    #move piece to graveyard
    if pieces[movement[3]][movement[4]] != (0, 0):
        if pieces[movement[3]][movement[4]][1] >= 1 and pieces[movement[3]][movement[4]][1] <= 6:
            for x in range(0, 2):
                if temp == 1:
                    break
                for y in range(0, 8):
                    if pieces[x][y] == (0, 0):
                        #pieces[movement[3]][movement[4]][0].move(SQUARE_SZ * (x - movement[3]), SQUARE_SZ * (y - movement[4]))
                        steppermove(pieces, (pieces[movement[3]][movement[4]][1], movement[3], movement[4], x, y))
                        pieces[x][y] = pieces[movement[3]][movement[4]]
                        temp = 1
                        break
        if pieces[movement[3]][movement[4]][1] >= 7 and pieces[movement[3]][movement[4]][1] <= 12:
            for x in range(10, 12):
                if temp == 1:
                    break
                for y in range(0, 8):
                    if pieces[x][y] == (0, 0):
                        #pieces[movement[3]][movement[4]][0].move(SQUARE_SZ * (x - movement[3]), SQUARE_SZ * (y - movement[4]))
                        steppermove(pieces, (pieces[movement[3]][movement[4]][1], movement[3], movement[4], x, y))
                        pieces[x][y] = pieces[movement[3]][movement[4]]
                        temp = 1
                        break        

    steppermove(pieces, movement)        

    #en passent
    if (movement[0] == BPAWN or movement[0] == WPAWN) and abs(movement[3] - movement[1]) == 1 and pieces[movement[3]][movement[4]] == (0, 0) and pieces[movement[3]][movement[2]] != (0, 0):
        movepiece(pieces, (pieces[movement[3]][movement[2]][1], movement[3], movement[2], movement[3], movement[2]))

    #move piece in array
    pieces[movement[3]][movement[4]] = pieces[movement[1]][movement[2]]
    pieces[movement[1]][movement[2]] = (0, 0) 

    #castling
    if movement == (WKING, 6, 0, 8, 0) and pieces[9][0][1] == WROOK:
        movepiece(pieces, (WROOK, 9, 0, 7, 0))
    if movement == (WKING, 6, 0, 4, 0) and pieces[2][0][1] == WROOK:
        movepiece(pieces, (WROOK, 2, 0, 5, 0))
    if movement == (BKING, 6, 7, 8, 7) and pieces[9][7][1] == BROOK:
        movepiece(pieces, (BROOK, 9, 7, 7, 7))
    if movement == (BKING, 6, 7, 4, 7) and pieces[2][7][1] == BROOK:
        movepiece(pieces, (BROOK, 2, 7, 5, 7))

#this functions moves the physical piece across the board without collision
def steppermove(pieces, movement):

    piece = pieces[movement[1]][movement[2]][0]
    rowdis = movement[3] - movement[1]
    coldis = movement[4] - movement[2]

    #diagnal movement if clear path
    if abs(rowdis) == abs(coldis):
        temp = 0
        for diag in range(1, abs(coldis)):
            if pieces[movement[1] + diag * int(rowdis / abs(coldis))][movement[2] + diag * int(coldis / abs(coldis))] != (0, 0):
                temp += 1
        if temp == 0:
            for y in range(0, abs(rowdis) * SQUARE_SZ):
                piece.move(rowdis / abs(rowdis), 0)
                time.sleep(.01)
                piece.move(0, coldis / abs(coldis))
                time.sleep(.01)
            return

    #row movement if clear path
    if rowdis == 0:
        temp = 0
        for y in range(1, abs(coldis)):
            if pieces[movement[1]][movement[2] + (y * int(coldis / abs(coldis)))] != (0, 0):
                temp += 1
        if temp == 0:    
            for y in range(0, abs(coldis) * SQUARE_SZ):
                piece.move(0, coldis / abs(coldis))
                time.sleep(.01)
            return

    #col movement if clear path
    if coldis == 0:
        temp = 0
        for x in range(1, abs(rowdis)):
            if pieces[movement[1] + (x * int(rowdis / abs(rowdis)))][movement[2]] != (0, 0):
                temp += 1
        if temp == 0:
            for x in range(0, abs(rowdis) * SQUARE_SZ):
                piece.move(rowdis / abs(rowdis), 0)
                time.sleep(.01)
            return
    
    #up or down indicator for end adjustment, where down is 1 and up -1
    uod = 0
    #left or right indicator for end adjustment, where left is -1 and right is 1       
    lor = 0 

    #determines the best path between spaces for rows
    if movement[1] < movement[3]:
        lor = -1
    elif movement[1] > movement[3]:
        lor = 1
    elif movement[1] < 6:
        lor = -1
    else:
        lor = 1
    for x in range(0, SQ_SZ_HALF):
        piece.move(-1 * lor, 0)
        time.sleep(.01)

    #determines the best path between spaces for cols
    if movement[4] < movement[2]:
        uod = 1
    elif movement[4] > movement[2]:
        uod = -1
    elif movement[4] < 4:
        uod = 1
    else:
        uod = -1

    #moves across the cols with the adjustment
    if coldis == 0:
        for y in range(0, SQ_SZ_HALF):
            piece.move(0, uod)
            time.sleep(.01)
    elif coldis > 0:        
        for y in range(-1 * uod * SQ_SZ_HALF, coldis * SQUARE_SZ):
            piece.move(0, coldis / abs(coldis))
            time.sleep(.01)
    else:
        for y in range(uod * SQ_SZ_HALF, abs(coldis) * SQUARE_SZ):
            piece.move(0, coldis / abs(coldis))
            time.sleep(.01)

    #moves across the rows
    if rowdis == 0:
        for x in range(0, SQ_SZ_HALF):
            piece.move(lor, 0)
            time.sleep(.01)
    elif rowdis > 0:
        for x in range(-1 * lor * SQ_SZ_HALF, abs(rowdis) * SQUARE_SZ):
            piece.move(rowdis / abs(rowdis), 0)
            time.sleep(.01)
    else:
        for x in range(lor * SQ_SZ_HALF, abs(rowdis) * SQUARE_SZ):
            piece.move(rowdis / abs(rowdis), 0)
            time.sleep(.01)

    #moves row adjustment
    for y in range(0, SQ_SZ_HALF):
        piece.move(0, uod * -1)
        time.sleep(.01)

#############################################
# Functions for resetting board             #
#############################################

def reset(pieces):
    temp = 1
    while temp == 1:
        temp = 0
        for x in range(0, 12):
            for y in range(0, 8):
                if pieces[x][y] != (0, 0):
                    moved = moveto(pieces, (x, y))
                    if moved == 0:
                        moveto(pieces, (x, y))
                        temp = 1

def closestFree(pieces, place):
    lor = uod = 0
    for x in range(0, 12):
        lor = place[0] + x
        if inRangeAndFree(pieces, (lor, place[1])) == 1:
            return (lor, place[1])
        uod = place[1] + x
        if inRangeAndFree(pieces, (lor, uod)) == 1:
            return (lor, uod)
        lor = place[0]
        if inRangeAndFree(pieces, (lor, uod)) == 1:
            return (lor, uod)
        lor = place[0] - x
        if inRangeAndFree(pieces, (lor, uod)) == 1:
            return (lor, uod)
        uod = place[1]
        if inRangeAndFree(pieces, (lor, uod)) == 1:
            return (lor, uod)
        uod = place[1] - x
        if inRangeAndFree(pieces, (lor, uod)) == 1:
            return (lor, uod)
        lor = place[0]
        if inRangeAndFree(pieces, (lor, uod)) == 1:
            return (lor, uod)
        lor = place[0] + x
        if inRangeAndFree(pieces, (lor, uod)) == 1:
            return (lor, uod)
    for x in range(2, 10):
        for y in range(2, 6):
            if inRangeAndFree(pieces, (x, y)):
                return (x, y)

def inRangeAndFree(pieces, place):
    if place[0] >= 2 and place[0] < 10 and place[1] >= 2 and place[1] < 6:
        if pieces[place[0]][place[1]] == (0, 0):
            return 1
    return 0

def moveto(pieces, place):
    destination = (0, 0)

    #using Bishop so it won't triger en passent accidentally
    if pieces[place[0]][place[1]][1] == WPAWN:
        if place[0] >= 2 and place[0] < 10 and place[1] == 1:
            return 1 
        for x in range(2, 10):
            if pieces[x][1] == (0, 0):
                movepiece(pieces, (WBISHOP, place[0], place[1], x, 1))
                return 1
            if pieces[x][6][1] != WPAWN:
                destination = (x, 1)

    if pieces[place[0]][place[1]][1] == BPAWN:
        if place[0] >= 2 and place[0] < 10 and place[1] == 6:
            return 1 
        for x in range(2, 10):
            if pieces[x][6] == (0, 0):
                movepiece(pieces, (BBISHOP, place[0], place[1], x, 6))
                return 1
            if pieces[x][6][1] != BPAWN:
                destination = (x, 6)

    if pieces[place[0]][place[1]][1] == WROOK:
        if (place[0] == 2 or place[0] == 9) and place[1] == 0:
            return 1
        if pieces[2][0] == (0, 0):
            movepiece(pieces, (WROOK, place[0], place[1], 2, 0))
            return 1
        if pieces[2][0][1] != WROOK:
            destination = (2, 0)
        if pieces[9][0] == (0, 0):
            movepiece(pieces, (WROOK, place[0], place[1], 9, 0))
            return 1
        if pieces[9][0][1] != WROOK:
            destination = (9, 0)

    if pieces[place[0]][place[1]][1] == BROOK:
        if (place[0] == 2 or place[0] == 9) and place[1] == 7:
            return 1
        if pieces[2][7] == (0, 0):
            movepiece(pieces, (BROOK, place[0], place[1], 2, 7))
            return 1
        if pieces[2][7][1] != BROOK:
            destination = (2, 7)
        if pieces[9][7] == (0, 0):
            movepiece(pieces, (BROOK, place[0], place[1], 9, 7))
            return 1
        if pieces[9][7][1] != BROOK:
            destination = (9, 7)

    if pieces[place[0]][place[1]][1] == WKNIGHT:
        if (place[0] == 3 or place[0] == 8) and place[1] == 0:
            return 1
        if pieces[3][0] == (0, 0):
            movepiece(pieces, (WKNIGHT, place[0], place[1], 3, 0))
            return 1
        if pieces[3][0][1] != WKNIGHT:
            destination = (3, 0)
        if pieces[8][0] == (0, 0):
            movepiece(pieces, (WKNIGHT, place[0], place[1], 8, 0))
            return 1
        if pieces[8][0][1] != WKNIGHT:
            destination = (8, 0)

    if pieces[place[0]][place[1]][1] == BKNIGHT:
        if (place[0] == 3 or place[0] == 8) and place[1] == 7:
            return 1
        if pieces[3][7] == (0, 0):
            movepiece(pieces, (BKNIGHT, place[0], place[1], 3, 7))
            return 1
        if pieces[3][7][1] != BKNIGHT:
            destination = (3, 7)
        if pieces[8][7] == (0, 0):
            movepiece(pieces, (BKNIGHT, place[0], place[1], 8, 7))
            return 1
        if pieces[8][7][1] != BKNIGHT:
            destination = (8, 7)

    if pieces[place[0]][place[1]][1] == WBISHOP:
        if (place[0] == 4 or place[0] == 7) and place[1] == 0:
            return 1
        if pieces[4][0] == (0, 0):
            movepiece(pieces, (WBISHOP, place[0], place[1], 4, 0))
            return 1
        if pieces[4][0][1] != WBISHOP:
            destination = (4, 0)
        if pieces[7][0] == (0, 0):
            movepiece(pieces, (WBISHOP, place[0], place[1], 7, 0))
            return 1
        if pieces[7][0][1] != WBISHOP:
            destination = (7, 0)

    if pieces[place[0]][place[1]][1] == BBISHOP:
        if (place[0] == 4 or place[0] == 7) and place[1] == 7:
            return 1
        if pieces[4][7] == (0, 0):
            movepiece(pieces, (BBISHOP, place[0], place[1], 4, 7))
            return 1
        if pieces[4][7][1] != BBISHOP:
            destination = (4, 7)
        if pieces[7][7] == (0, 0):
            movepiece(pieces, (BBISHOP, place[0], place[1], 7, 7))
            return 1
        if pieces[7][7][1] != BBISHOP:
            destination = (7, 7)

    if pieces[place[0]][place[1]][1] == WQUEEN:
        if place[0] == 5 and place[1] == 0:
            return 1
        if pieces[5][0] == (0, 0):
            movepiece(pieces, (WQUEEN, place[0], place[1], 5, 0))
            return 1
        if pieces[5][0][1] != WQUEEN:
            destination = (5, 0)

    if pieces[place[0]][place[1]][1] == BQUEEN:
        if place[0] == 5 and place[1] == 7:
            return 1
        if pieces[5][7] == (0, 0):
            movepiece(pieces, (BQUEEN, place[0], place[1], 5, 7))
            return 1
        if pieces[5][7][1] != BQUEEN:
            destination = (5, 7)

    if pieces[place[0]][place[1]][1] == WKING:
        if place[0] == 6 and place[1] == 0:
            return 1
        if pieces[6][0] == (0, 0):
            movepiece(pieces, (WKING, place[0], place[1], 6, 0))
            return 1
        if pieces[6][0][1] != WKING:
            destination = (6, 0)

    if pieces[place[0]][place[1]][1] == BKING:
        if place[0] == 6 and place[1] == 7:
            return 1
        if pieces[6][7] == (0, 0):
            movepiece(pieces, (BKING, place[0], place[1], 6, 7))
            return 1
        if pieces[6][7][1] != BKING:
            destination = (6, 7)

    #bishop to make sure it does not trigger special moves
    away = closestFree(pieces, destination)
    movepiece(pieces, (BBISHOP, destination[0], destination[1], away[0], away[1]))

    return 0

#############################################
# Main Function                             #
#############################################

def main():

    # Helper parses return value from C simulator.
    def parseSimReturn(retval):
        try:
            isValid = retval[0]
            moves  = retval[1:]
            return (isValid, moves)
        except:
            return (retval, b'')

    # Set up graphics and board
    (win, squares) = setup_graphics()
    (win, squares, pieces) = setup_board(win, squares)

    # Text screen is initialized
    t3 = Text(Point(370, 450), "")

    # Automatically set up connection
    state = NOTCONNECTED
    sock = setup_connection()
    sock.sendto(b'.connect', (SERVER, PORT))
    response = sock.recv(1)

    # Will change based on when client connected to server.
    mycolor = WHITE
    displaytext = ""
    
    if response == b'\x01':
        displaytext = "Connected."
        state = CONNECTED
        mycolor = WHITE
    elif response == b'\x03':
        displaytext = "Connected."
        state = CONNECTED
        mycolor = BLACK

    t3.undraw()
    t3 = Text(Point(370, 450), displaytext)
    t3.draw(win)

    # Program is running.
    while 1:

        while state == CONNECTED:

            print("CONNECTED")
            point = win.getMouse()

            # clicked on "Ready" button       
            if(point.x >= READY_BTN_TOPL_X and point.x <= READY_BTN_BOTR_X and point.y >= READY_BTN_TOPL_Y and point.y <= READY_BTN_BOTR_Y):

                sock = setup_connection()
                sock.sendto(b'.ready', (SERVER, PORT))
                response = sock.recv(1)

                # May transition straight to MOVING/WAITING from CONNECTED.
                displaytext = ""
                if response == b'\x11':
                    displaytext = "Ready."
                    state = READY
                # Python may turn \x21 character into '!', \x22 into '"'. Check for both.
                if response in [b'\x21', b'!']:
                    displaytext = "Your turn."
                    state = MOVING
                if response in [b'\x22', b'"']:
                    displaytext = "Their turn."
                    state = WAITING
                
                t3.undraw()
                t3 = Text(Point(370, 450), displaytext)
                t3.draw(win)

            # clicked on "End" button       
            if(point.x >= END_BTN_TOPL_X and point.x <= END_BTN_BOTR_X and point.y >= END_BTN_TOPL_Y and point.y <= END_BTN_BOTR_Y):
                sock = setup_connection()
                sock.sendto(b'.end', (SERVER, PORT))
                return

            # TODO: clicked on "Reset" button

        while state == READY:

            print("READY")
            
            sock = setup_connection()
            sock.sendto(b'.gib', (SERVER, PORT))
            response = sock.recv(1)
            
            while response not in [b'\x21', b'\x22', b'!', b'"']:
                time.sleep(5)
                
                sock = setup_connection()
                sock.sendto(b'.gib', (SERVER, PORT))
                response = sock.recv(1)
                
                print(response)
                        
            displaytext = ""
            if response == b'\x11':
                displaytext = "Ready."
                state = READY
            # Python may turn \x21 character into '!', \x22 into '"'. Check for both.
            if response in [b'\x21', b'!']:
                displaytext = "Your turn."
                state = MOVING
            if response in [b'\x22', b'"']:
                displaytext = "Their turn."
                state = WAITING
                
            t3.undraw()
            t3 = Text(Point(370, 450), displaytext)
            t3.draw(win)            

##            point = win.getMouse()
##            
##            # clicked on "End" button       
##            if(point.x >= END_BTN_TOPL_X and point.x <= END_BTN_BOTR_X and point.y >= END_BTN_TOPL_Y and point.y <= END_BTN_BOTR_Y):
##                sock = setup_connection()
##                sock.sendto(b'.end', (SERVER, PORT))
##                return

            # TODO: clicked on "Reset" button
            
        while state == WAITING:

            # Print state to console and GUI screen.
            print("WAITING")

            t3.undraw()
            t3 = Text(Point(370, 450), "Their turn.")
            t3.draw(win)

            # Clear old value.
            dataOpponent = b''
            
            sock = setup_connection()
            sock.sendto(b'.gib', (SERVER, PORT))
            dataOpponent = sock.recv(8)
            
            while len(dataOpponent) != 8:
                time.sleep(5)
                
                sock = setup_connection()
                sock.sendto(b'.gib', (SERVER, PORT))
                dataOpponent = sock.recv(8)
                
                print(dataOpponent)

                # Python may turn \x33 into '1'. Check for both.
                if dataOpponent in [b'\x33', b'3']:
                    state = CONNECTED
                    break # out of recv loop.

            if dataOpponent in [b'\x33', b'3']:
                state = CONNECTED
                break # out of WAITING loop.

            # Create move set.
            movementOpp1 = (pieces[dataOpponent[1]][dataOpponent[0]], dataOpponent[1], dataOpponent[0], dataOpponent[3], dataOpponent[2])
            movementOpp2 = (pieces[dataOpponent[5]][dataOpponent[4]], dataOpponent[5], dataOpponent[4], dataOpponent[7], dataOpponent[6])

            # If movement2 exists, it must be done, and done before movement1.
            if movementOpp2[1:] != (0, 0, 0, 0):
                print(movementOpp2)
                movepiece(pieces, movementOpp2)

            # movement1 only exists when dataOpponent is non-empty or non-junk. It must always be done.
            print(movementOpp1)
            movepiece(pieces, movementOpp1)

            # Pawn promotion
            if pieces[dataOpponent[3]][dataOpponent[2]][1] == WPAWN and dataOpponent[2] == 7:

                pieces[dataOpponent[3]][dataOpponent[2]][0].undraw()
                pieces[dataOpponent[3]][dataOpponent[2]] = (Text(Point((dataOpponent[3] * SQUARE_SZ) + (SQ_SZ_HALF), 375), '♕'), WQUEEN)   
                pieces[dataOpponent[3]][dataOpponent[2]][0].setSize((SQ_SZ_HALF))
                pieces[dataOpponent[3]][dataOpponent[2]][0].draw(win)

            elif pieces[dataOpponent[3]][dataOpponent[2]][1] == BPAWN and dataOpponent[2] == 0:

                pieces[dataOpponent[3]][dataOpponent[2]][0].undraw()
                pieces[dataOpponent[3]][dataOpponent[2]] = (Text(Point((dataOpponent[3] * SQUARE_SZ) + (SQ_SZ_HALF), (SQ_SZ_HALF)), '♛'), BQUEEN)
                pieces[dataOpponent[3]][dataOpponent[2]][0].setSize((SQ_SZ_HALF))
                pieces[dataOpponent[3]][dataOpponent[2]][0].draw(win)

            # Clear these values after they have been executed.
            movementOpp1 = ((0, 0), 0, 0, 0, 0)
            movementOpp2 = ((0, 0), 0, 0, 0, 0)

            # Finally, transition to MOVING state.
            state = MOVING

        while state == MOVING:

            # Print state to console and GUI screen.
            print("MOVING")

            t3.undraw()
            t3 = Text(Point(370, 450), "Your turn.")
            t3.draw(win)

            # Get user input (no harm in calculating fromrow and fromcol now).
            point = win.getMouse()            
            fromrow = point.x // SQUARE_SZ
            fromcol = point.y // SQUARE_SZ

            # clicked on "End" button       
            if(point.x >= END_BTN_TOPL_X and point.x <= END_BTN_BOTR_X and point.y >= END_BTN_TOPL_Y and point.y <= END_BTN_BOTR_Y):
                sock = setup_connection()
                sock.sendto(b'.end', (SERVER, PORT))

                state = CONNECTED
                break

            # Not clicked in board space, start over.
            if(point.y > 400 or point.x < 100 and point.x > 500):
                continue

            # Determines if piece was selected, or an empty square.
            temp = pieces[fromrow][fromcol]            
            if temp == (0, 0):
                continue

            squares[fromrow][fromcol].setFill("lime")
            
            point2 = win.getMouse()
            torow = point2.x // SQUARE_SZ
            tocol = point2.y // SQUARE_SZ

            # Not clicked in board space again, start over.
            if(point2.y > 400 or point2.x < 100 or point2.x > 500):
                continue
            
            if fromrow < 2 or fromrow > 9:
                squares[fromrow][fromcol].setFill("linen")
            elif (fromrow + fromcol) % 2 == 0:
                squares[fromrow][fromcol].setFill("gray")
            else: 
                squares[fromrow][fromcol].setFill("white")

            # Helper for creating msg.
            def concat(i):
                 return b' ' + str(i).encode()
                
            #movement = (piece-to-move, ...)
            tempMovement = (pieces[fromrow][fromcol][1], fromrow, fromcol, torow, tocol)

            # mixup during, microcontroller code asks for rows before cols.
            # Removed piece from msg, server/simulator will expect only 4 numbers for XY positions.
            msg = b'.move' + concat(tempMovement[2]) + concat(tempMovement[1]) + concat(tempMovement[4]) + concat(tempMovement[3])

            sock = setup_connection()
            sock.sendto(msg, (SERVER, PORT))
            dataSelf = sock.recv(9)
            
            print(dataSelf)
            (isValid, moves) = parseSimReturn(dataSelf)
        
            print(isValid)
            if isValid > 0:

                # Checkmate (must be checked before movement
                # b/c moves may be filled with zeroes).
                if isValid == 3:

                    t3.undraw()
                    print(moves)
                    if moves == b'\x00\x00\x00\x00\x00\x00\x00\x00':
                        t3 = Text(Point(370, 450), "You lost.")
                        t3.draw(win)
                        state = CONNECTED
                        break
                    else:
                        t3 = Text(Point(370, 450), "You won.")
                        t3.draw(win)
                    
                # Create move set.
                movement1 = (pieces[moves[1]][moves[0]], moves[1], moves[0], moves[3], moves[2])
                movement2 = (pieces[moves[5]][moves[4]], moves[5], moves[4], moves[7], moves[6])

                # If movement2 exists, you must do it, and do it before movement1.
                if movement2[1:] != (0, 0, 0, 0):
                    print(movement2)
                    movepiece(pieces, movement2)

                # movement1 only exists if move was valid, so always do it.
                print(movement1)
                movepiece(pieces, movement1)

                # Pawn promotion (should be checked after movement).
                if isValid == 2:

                    pieces[moves[3]][moves[2]][0].undraw()
                    
                    if mycolor == WHITE:
                        pieces[moves[3]][moves[2]] = (Text(Point((moves[3] * SQUARE_SZ) + (SQ_SZ_HALF), 375), '♕'), WQUEEN)
                    elif mycolor == BLACK:
                        pieces[moves[3]][moves[2]] = (Text(Point((moves[3] * SQUARE_SZ) + (SQ_SZ_HALF), (SQ_SZ_HALF)), '♛'), BQUEEN)
                        
                    pieces[moves[3]][moves[2]][0].setSize((SQ_SZ_HALF))
                    pieces[moves[3]][moves[2]][0].draw(win)

                # Clear these values after they have been executed.
                movement1 = ((0, 0), 0, 0, 0, 0)
                movement2 = ((0, 0), 0, 0, 0, 0)

                # Finally, transition state.
                if isValid == 3:
                    state = CONNECTED
                else:
                    state = WAITING

                # State only changes when move is valid, otherwise player must try again.
        
#############################################
# Call to Main Function                     #
############################################# 

main()
