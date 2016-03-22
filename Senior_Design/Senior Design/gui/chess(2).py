from graphics import *
import subprocess


def main():

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

    win = GraphWin('Chess', 600, 400) # give title and dimensions

    squares = [[0 for x in range(8)] for y in range(12)]

    for x in range(0, 12):
        for y in range(0,8):
            squares[x][y] = Rectangle(Point(x*50, y*50), Point(x*50+50, y*50+50))
            if x < 2 or x > 9:
                squares[x][y].setFill("linen")
            elif (x + y) % 2 == 0:
                squares[x][y].setFill("gray")
            else: 
                squares[x][y].setFill("white")
            squares[x][y].draw(win)

#white pieces

    pieces = [[0 for x in range(8)] for y in range(12)]

    for x in range(0, 12):
        for y in range(0,8):
            pieces[x][y] = (0, 0)

    pieces[2][0] = (Text(Point(125, 25), '♖'), WROOK)
    pieces[2][0][0].setSize(25)
    pieces[2][0][0].draw(win) 

    pieces[3][0] = (Text(Point(175, 25), '♘'), WKNIGHT)
    pieces[3][0][0].setSize(25)
    pieces[3][0][0].draw(win) 

    pieces[4][0] = (Text(Point(225, 25), '♗'), WBISHOP)
    pieces[4][0][0].setSize(25)
    pieces[4][0][0].draw(win) 

    pieces[5][0] = (Text(Point(275, 25), '♕'), WQUEEN)
    pieces[5][0][0].setSize(25)
    pieces[5][0][0].draw(win) 

    pieces[6][0] = (Text(Point(325, 25), '♔'), WKING)
    pieces[6][0][0].setSize(25)
    pieces[6][0][0].draw(win) 

    pieces[7][0] = (Text(Point(375, 25), '♗'), WBISHOP)
    pieces[7][0][0].setSize(25)
    pieces[7][0][0].draw(win) 

    pieces[8][0] = (Text(Point(425, 25), '♘'), WKNIGHT)
    pieces[8][0][0].setSize(25)
    pieces[8][0][0].draw(win) 

    pieces[9][0] = (Text(Point(475, 25), '♖'), WROOK)
    pieces[9][0][0].setSize(25)
    pieces[9][0][0].draw(win) 
    
    for x in range(2, 10):
        pieces[x][1] = (Text(Point(x*50 + 25, 75), '♙'), WPAWN)
        pieces[x][1][0].setSize(25)
        pieces[x][1][0].draw(win) 

#black pieces

    pieces[2][7] = (Text(Point(125, 375), '♜'), BROOK)
    pieces[2][7][0].setSize(25)
    pieces[2][7][0].draw(win) 

    pieces[3][7] = (Text(Point(175, 375), '♞'), BKNIGHT)
    pieces[3][7][0].setSize(25)
    pieces[3][7][0].draw(win) 

    pieces[4][7] = (Text(Point(225, 375), '♝'), BBISHOP)
    pieces[4][7][0].setSize(25)
    pieces[4][7][0].draw(win) 

    pieces[5][7] = (Text(Point(275, 375), '♛'), BQUEEN)
    pieces[5][7][0].setSize(25)
    pieces[5][7][0].draw(win) 

    pieces[6][7] = (Text(Point(325, 375), '♚'), BKING)
    pieces[6][7][0].setSize(25)
    pieces[6][7][0].draw(win) 

    pieces[7][7] = (Text(Point(375, 375), '♝'), BBISHOP)
    pieces[7][7][0].setSize(25)
    pieces[7][7][0].draw(win) 

    pieces[8][7] = (Text(Point(425, 375), '♞'), BKNIGHT)
    pieces[8][7][0].setSize(25)
    pieces[8][7][0].draw(win) 

    pieces[9][7] = (Text(Point(475, 375), '♜'), BROOK)
    pieces[9][7][0].setSize(25)
    pieces[9][7][0].draw(win) 
    
    for x in range(2, 10):
        pieces[x][6] = (Text(Point(x*50 + 25, 325), '♟'), BPAWN)
        pieces[x][6][0].setSize(25)
        pieces[x][6][0].draw(win)  

    # movepiece(win, pieces, (1, 2, 1, 2, 3))
    # movepiece(win, pieces, (1, 2, 6, 2, 4))
    # movepiece(win, pieces, (1, 2, 0, 2, 2))
    # movepiece(win, pieces, (1, 2, 7, 2, 5))
    # movepiece(win, pieces, (1, 2, 2, 3, 2))
    # movepiece(win, pieces, (1, 2, 5, 3, 5))

    

    while 1:
        point = win.getMouse()
        fromrow = point.x//50
        fromcol = point.y//50
        if pieces[fromrow][fromcol] == (0, 0):
            return
        squares[fromrow][fromcol].setFill("lime")
        point = win.getMouse()
        torow = point.x//50
        tocol = point.y//50
        if fromrow < 2 or fromrow > 9:
            squares[fromrow][fromcol].setFill("linen")
        elif (fromrow + fromcol) % 2 == 0:
            squares[fromrow][fromcol].setFill("gray")
        else: 
            squares[fromrow][fromcol].setFill("white")

        movepiece(win, pieces, (pieces[fromrow][fromcol][1], fromrow, fromcol, torow, tocol))

#move is a 5 tuple of (piece, fromrow, fromcol, torow, tocol)

def movepiece(win, pieces, movement):

    # value = ''
    # for x in range(0,8):
    #     for y in range(0,12):
    #         value += 'str(pieces[' + str(y) + '][' + str(x) + '][1]), '
    value = subprocess.call(['./legal.exe', str(movement[0]), str(movement[1]), str(movement[2]), str(movement[3]), str(movement[4]), str(pieces[0][0][1]), str(pieces[1][0][1]), str(pieces[2][0][1]), str(pieces[3][0][1]), str(pieces[4][0][1]), str(pieces[5][0][1]), str(pieces[6][0][1]), str(pieces[7][0][1]), str(pieces[8][0][1]), str(pieces[9][0][1]), str(pieces[10][0][1]), str(pieces[11][0][1]), str(pieces[0][1][1]), str(pieces[1][1][1]), str(pieces[2][1][1]), str(pieces[3][1][1]), str(pieces[4][1][1]), str(pieces[5][1][1]), str(pieces[6][1][1]), str(pieces[7][1][1]), str(pieces[8][1][1]), str(pieces[9][1][1]), str(pieces[10][1][1]), str(pieces[11][1][1]), str(pieces[0][2][1]), str(pieces[1][2][1]), str(pieces[2][2][1]), str(pieces[3][2][1]), str(pieces[4][2][1]), str(pieces[5][2][1]), str(pieces[6][2][1]), str(pieces[7][2][1]), str(pieces[8][2][1]), str(pieces[9][2][1]), str(pieces[10][2][1]), str(pieces[11][2][1]), str(pieces[0][3][1]), str(pieces[1][3][1]), str(pieces[2][3][1]), str(pieces[3][3][1]), str(pieces[4][3][1]), str(pieces[5][3][1]), str(pieces[6][3][1]), str(pieces[7][3][1]), str(pieces[8][3][1]), str(pieces[9][3][1]), str(pieces[10][3][1]), str(pieces[11][3][1]), str(pieces[0][4][1]), str(pieces[1][4][1]), str(pieces[2][4][1]), str(pieces[3][4][1]), str(pieces[4][4][1]), str(pieces[5][4][1]), str(pieces[6][4][1]), str(pieces[7][4][1]), str(pieces[8][4][1]), str(pieces[9][4][1]), str(pieces[10][4][1]), str(pieces[11][4][1]), str(pieces[0][5][1]), str(pieces[1][5][1]), str(pieces[2][5][1]), str(pieces[3][5][1]), str(pieces[4][5][1]), str(pieces[5][5][1]), str(pieces[6][5][1]), str(pieces[7][5][1]), str(pieces[8][5][1]), str(pieces[9][5][1]), str(pieces[10][5][1]), str(pieces[11][5][1]), str(pieces[0][6][1]), str(pieces[1][6][1]), str(pieces[2][6][1]), str(pieces[3][6][1]), str(pieces[4][6][1]), str(pieces[5][6][1]), str(pieces[6][6][1]), str(pieces[7][6][1]), str(pieces[8][6][1]), str(pieces[9][6][1]), str(pieces[10][6][1]), str(pieces[11][6][1]), str(pieces[0][7][1]), str(pieces[1][7][1]), str(pieces[2][7][1]), str(pieces[3][7][1]), str(pieces[4][7][1]), str(pieces[5][7][1]), str(pieces[6][7][1]), str(pieces[7][7][1]), str(pieces[8][7][1]), str(pieces[9][7][1]), str(pieces[10][7][1]), str(pieces[11][7][1])])
    print(value)
    rowdis = movement[3] - movement[1]
    coldis = movement[4] - movement[2]
    pieces[movement[1]][movement[2]][0].move(rowdis * 50, coldis * 50)
    pieces[movement[3]][movement[4]] = pieces[movement[1]][movement[2]]
    pieces[movement[1]][movement[2]] = (0, 0)

main()