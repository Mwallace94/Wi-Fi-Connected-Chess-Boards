import socketserver
import socket
from collections import defaultdict
import subprocess

PORT = 666
IP = '192.168.173.1'

CPORT = 656
CIP = '127.0.0.1'

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

                def move(args):

                        # Helper converts int arguments to byte sequence.
                        def args2b(args):
                                bargs = []
                                for b in args:
                                        bargs += [int(b)]
                                return bytes(bargs)

                        # Helper parses return value from C simulator.
                        def parseSimReturn(retval):
                                isValid    = retval[0]
                                moves  = retval[0:]
                                return (isValid, moves)

                        if self.players[0] == (self.client_address[0], PORT):
                                if 1:#self.pstates[0] == MOVING:
                                        bargs = args2b(args)
                                        print(bargs)
                                        csock.sendto(bargs, (CIP, CPORT))
                                        
                                        # 8 validity bits, 32 move bits, 32 move bits
                                        retval = csock.recv(9)
                                        (isValid, moves) = parseSimReturn(retval)
                                        print(retval)
                                        
                                        # Regular valid move
                                        if isValid == 1:
                                                self.request.sendto(retval, self.players[0])
                                                self.request.sendto(moves, self.players[1])
                                                self.pstates[0] = WAITING
                                                self.pstates[1] = MOVING
                                                self.response[0] = b'22'
                                                
                                        # Pawn promotion, prompt for promotion argument
                                        elif isValid == 2:
                                                self.request.sendto(retval, self.players[0])
                                                self.request.sendto(moves, self.players[1])
                                                self.response[0] = b'24'
                                                
                                        else:
                                                self.request.sendto(isValid, self.players[0])
                                                self.response[0] = b'21'
                                        
                                else:
                                        self.request.sendto(b'Wait.', self.client_address)
                                        self.response[0] = b'22'
                                
                        elif self.players[1] == (self.client_address[0], PORT):
                                if 1:#self.pstates[1] == MOVING:
                                        bargs = args2b(args)
                                        print(bargs)
                                        csock.sendto(bargs, (CIP, CPORT))
                                        
                                        # 8 validity bits, 32 move bits, 32 move bits
                                        retval = csock.recv(9)
                                        (isValid, moves) = parseSimReturn(retval)
                                        print(retval)
                                        
                                        # Regular valid move
                                        if isValid == 1:
                                                self.request.sendto(retval, self.players[1])
                                                self.request.sendto(moves, self.players[0])
                                                self.pstates[0] = MOVING
                                                self.pstates[1] = WAITING
                                                self.response[0] = b'21'
                                                
                                        # Pawn promotion, prompt for promotion argument
                                        elif isValid == 2:
                                                self.request.sendto(retval, self.players[1])
                                                self.request.sendto(moves, self.players[0])
                                                self.response[0] = b'25'
                                                
                                        else:
                                                self.request.sendto(isValid, self.players[1])
                                                self.response[0] = b'22'
                                else:
                                        self.request.sendto(b'Wait.', self.client_address)
                                        self.response[0] = b'21'

                        else:
                                self.request.sendto(b'Who?', self.client_address)
                                self.response[0] = b'29' # Nobody will respond to this...

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
                                    
try:

        #Set up link with C chess board.
        csock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        csock.connect((CIP, CPORT))

        #Create a web server and define the handler to manage requests.        
        server = socketserver.TCPServer((IP, PORT), myHandler)
        print('Started TCP server at ', IP, ' on port ' , PORT, '.')
        server.serve_forever()
        
except KeyboardInterrupt:
        print('^C received, shutting down the web server.')
        server.socket.close()
