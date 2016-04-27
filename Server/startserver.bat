@echo off

:start
   cd /d C:\Users\Kyle\Downloads\classes\Senior_Design\WiFiChessBoard
   netsh wlan start hostednetwork
   timeout 2
   start call .\ChessSimulation\chessgame.exe
   start call python .\Server\tcsrv.py
   start /b call python .\VirtualClient\chess.py
   
   