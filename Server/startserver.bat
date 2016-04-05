@echo off

:start
   cd /d E:\Documents\GitHub\WiFiChessBoard
   netsh wlan start hostednetwork
   timeout 2
   start call .\ChessSimulation\chessgame.exe
   start call python .\Server\tcsrv.py
   start /b call python .\VirtualClient\chess.py
   
   