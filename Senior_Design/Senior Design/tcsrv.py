import socketserver
from collections import defaultdict

PORT = 666
IP = '192.168.173.1'

#Pieces
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

#States
NOTCONNECTED = 0
CONNECTED = 1
READY = 2
WAITING = 3
MOVING = 4

#This class will handles any incoming request.
class myHandler(socketserver.BaseRequestHandler):

        response = [b''] # Needs brackets, but not sure why.
        players = ['','']
        pstates = [NOTCONNECTED, NOTCONNECTED]
        board = [[0 for x in range(12)] for x in range(8)]

        board[2][0] = WROOK
        board[3][0] = WKNIGHT
        board[4][0] = WBISHOP
        board[5][0] = WQUEEN
        board[6][0] = WKING
        board[7][0] = WBISHOP
        board[8][0] = WKNIGHT
        board[9][0] = WROOK

        for x in range(2, 10):
                board[x][1] = WPAWN

        board[2][7] = BROOK
        board[3][7] = BKNIGHT
        board[4][7] = BBISHOP
        board[5][7] = BQUEEN
        board[6][7] = BKING
        board[7][7] = BBISHOP
        board[8][7] = BKNIGHT
        board[9][7] = BROOK

        for x in range(2, 10):
                board[x][7] = BPAWN

        def handle(self):

                self.rawdata = self.request.recv(1024).strip()

                def connect(args):
                        
                        if self.players[0] == '':
                                if self.pstates[0] == NOTCONNECTED:
                                        self.players[0] = (self.client_address[0], PORT)
                                        self.pstates[0] = CONNECTED
                                        self.request.sendto(b'P1.', self.client_address)
                                        self.response[0] = b'01'
                                else:
                                        self.request.sendto(b'Err:pstates[0].', self.client_address)
                                        self.response[0] = b'02'
                                        
                        # Same player cannot connect twice.
                        elif self.players[1] == '' and self.players[0][0] != self.client_address[0]:
                                if self.pstates[1] == NOTCONNECTED:
                                        self.players[1] = (self.client_address[0], PORT)
                                        self.pstates[1] = CONNECTED
                                        self.request.sendto(b'P2.', self.client_address)
                                        self.response[0] = b'03'
                                else:
                                        self.request.sendto(b'Err:pstates[1].', self.client_address)
                                        self.response[0] = b'04'
                                        
                        else:
                                if self.players[0][0] == self.client_address[0] or self.players[1][0] == self.client_address[0]:
                                        self.request.sendto(b'Connected.', self.client_address)
                                        self.response[0] = b'05'
                                else:
                                        self.request.sendto(b'Closed.', self.client_address)
                                        self.response[0] = b'06'

                def ready(args):
                        
                        if self.players[0] == (self.client_address[0], PORT):
                                if self.pstates[0] == CONNECTED:
                                        self.pstates[0] = READY
                                        self.request.sendto(b'Ready.', self.client_address)
                                        self.response[0] = b'11'
                                elif self.pstates[0] == READY:
                                        self.request.sendto(b'Wait.', self.client_address)
                                        self.response[0] = b'12'
                                else:
                                        self.request.sendto(b'Err:pstates[0].', self.client_address)
                                        self.response[0] = b'13'
                                
                        elif self.players[1] == (self.client_address[0], PORT):
                                if self.pstates[1] == CONNECTED:
                                        self.pstates[1] = READY
                                        self.request.sendto(b'Ready.', self.client_address)
                                        self.response[0] = b'14'
                                elif self.pstates[1] == READY:
                                        self.request.sendto(b'Wait.', self.client_address)
                                        self.response[0] = b'15'
                                else:
                                        self.request.sendto(b'Err:pstates[1].', self.client_address)
                                        self.response[0] = b'16'

                        # Start game when both players are ready.
                        if self.pstates == [READY, READY]:
                                self.pstates[0] = MOVING
                                self.pstates[1] = WAITING
                                self.request.sendto(b'Go.', self.players[0])
                                self.request.sendto(b'Wait.', self.players[1])
                                self.response[0] = b'21'

##                def start(args):
##                        if self.pstates == [READY, READY]:
##                                self.pstates[0] = MOVING
##                                self.pstates[1] = WAITING
##                                self.request.sendto(b'Go.', self.players[0])
##                                self.request.sendto(b'Wait.', self.players[1])
##                                self.response[0] = b'21'
##                        else:
##                                self.request.sendto(b'Err:pstates.', self.client_address)
##                                self.response[0] = b'22'

                def move(args):
                        if self.players[0] == (self.client_address[0], PORT):
                                if self.pstates[0] == MOVING:
                                        if 1: # replace with legality check
                                                self.request.sendto(args, self.players[1])
                                                self.pstates[0] = WAITING
                                                self.pstates[1] = MOVING
                                                self.response[0] = b'22'
                                        else:
                                                self.request.sendto(b'Invalid.', self.client_address)
                                                self.response[0] = b'21'
                                        
                                else:
                                        self.request.sendto(b'Wait.', self.client_address)
                                        self.response[0] = b'22'
                                
                        elif self.players[1] == (self.client_address[0], PORT):
                                if self.pstates[1] == MOVING:
                                        if 1:
                                                self.request.sendto(args, self.players[0])
                                                self.pstates[0] = MOVING
                                                self.pstates[1] = WAITING
                                                self.response[0] = b'21'
                                        else:
                                                self.request.sendto(b'Invalid.', self.client_address)
                                                self.response[0] = b'22'
                                else:
                                        self.request.sendto(b'Wait.', self.client_address)
                                        self.response[0] = b'21'

                        else:
                                self.request.sendto(b'Who?', self.client_address)
                                self.response[0] = b'23' # Nobody will respond to this...

                def end(args):
                        if self.players[0] != '':
                                self.request.sendto(b'Finished.', self.players[0])
                        if self.players[1] != '':
                                self.request.sendto(b'Finished.', self.players[1])
                        self.players[0] = ''
                        self.players[1] = ''
                        self.pstates[0] = NOTCONNECTED
                        self.pstates[1] = NOTCONNECTED
                        self.response[0] = b'00'
                        
                def emptyinput(args):
                        self.request.sendto(b'Heartbeat.', self.client_address)
                        self.response[0] = b'00'

                def corruptinput(args):
                        self.request.sendto(b'What?', self.client_address)
                        self.response[0] = b'FF'
                
                option = {b'.' : emptyinput,
                          b'.connect' : connect,
                          b'.ready' : ready,
                          #b'.start' : start,
                          b'.move' : move,
                          b'.end' : end
                          }

                print(self.client_address[0], ' : ', self.rawdata)
                
                data = self.rawdata.split()
                if data:
                        command = data[0]
                        args = data[1:]
                        option.get(command, corruptinput)(args) # corruptinput is a default for bad inputs

                print(self.players, self.pstates)
                print(self.response[0])
                self.response[0] = b''
                
##                if command == b'.':
##                        
##                        if self.response[0] != b'':
##                                
##                                if self.players[0] == (self.client_address[0], PORT):
##                                        self.request.sendto(self.response[0], self.players[1])
##                                        self.pstates[0] = WAITING
##                                        self.pstates[1] = MOVING
##                                        
##                                elif self.players[1] == (self.client_address[0], PORT):
##                                        self.request.sendto(self.response[0], self.players[0])
##                                        self.pstates[0] = MOVING
##                                        self.pstates[1] = WAITING
##                                        
##                                else:
##                                        self.request.sendto(b'Wait', self.client_address)
##                                
##                        else:
##                                if self.players[0] == (self.client_address[0], PORT):
##                                        #self.request.sendto(b'Unique1', self.players[1])
##                                        self.pstates[0] = WAITING
##                                        self.pstates[1] = MOVING
##                                        
##                                elif self.players[1] == (self.client_address[0], PORT):
##                                        #self.request.sendto(b'Unique2', self.players[0])
##                                        self.pstates[0] = MOVING
##                                        self.pstates[1] = WAITING
##                                        
##                                else:
##                                        self.request.sendto(b'Wait', self.client_address)
##                                
##                        self.response[0] = b''
##                if command == b'.1':
##
##                        if self.players[0] == '':
##                                self.players[0] = (self.client_address[0], PORT)
##                                self.pstates[0] = CONNECTED
##                                self.request.sendto(b'P1', self.client_address)
##                                
##                        elif self.players[1] == '' and self.players[0][0] != self.client_address[0]:
##                                self.players[1] = (self.client_address[0], PORT)
##                                self.pstates[1] = CONNECTED
##                                self.request.sendto(b'P2', self.client_address)
##
##                        else:
##                                self.request.sendto(b'Closed', self.client_address)
##                        
##                        self.response[0] = b'1F'
##                if command == b'.2':
##
##                        if self.players[0] == (self.client_address[0], PORT):
##                                self.request.sendto(b'3F', self.players[1])
##                                self.pstates[0] = WAITING
##                                self.pstates[1] = MOVING
##                                
##                        elif self.players[1] == (self.client_address[0], PORT):
##                                self.request.sendto(b'4F', self.players[0])
##                                self.pstates[0] = MOVING
##                                self.pstates[1] = WAITING
##
##                        else:
##                                self.request.sendto(b'Wait', self.client_address)
##
##                        
##                        self.response[0] = b'2F'
##                if command == b'.3':
##                        self.request.sendto(b'1B', self.players[0])
##                        self.request.sendto(b'1B', self.players[1])
##                        self.response[0] = b'1B'
##                if command == b'.4':
##                        self.request.sendto(b'2B', self.players[0])
##                        self.request.sendto(b'2B', self.players[1])
##                        self.response[0] = b'2B'
##                print(self.response[0])
                        
try:
        #Create a web server and define the handler to manage requests.
        server = socketserver.TCPServer((IP, PORT), myHandler)
        print('Started TCP server at ', IP, ' on port ' , PORT, '.')
        server.serve_forever()
        
except KeyboardInterrupt:
        print('^C received, shutting down the web server.')
        server.socket.close()
