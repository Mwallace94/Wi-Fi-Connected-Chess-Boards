@echo off

:start
   cd /d E:\Documents\GitHub\WiFiChessBoard\WiFiChessBoard\
   netsh wlan start hostednetwork
   timeout 5
   start call .\ChessSimulation\chessgame.exe
   start call python .\Server\tcsrv.py
   start /b call python .\VirtualClient\chess.py
   
   