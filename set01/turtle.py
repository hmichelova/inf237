#!/usr/bin/python3

import sys

def createBoard():
    board = []
    for i in range(8):
        board.append(list(input()))

    return board

def nextPosition(x, y, orientation):
    if orientation == 0:
        return x, y - 1 
    
    if orientation == 1:
        return x + 1, y 
    
    if orientation == 2:
        return x, y + 1 
    
    if orientation == 3:
        return x - 1, y 
    

def makeMove(x, y, orientation, board):
    newX, newY = nextPosition(x, y, orientation)
    
    if newX < 0 or newX > 7 or newY < 0 or newY > 7 or board[newY][newX] in ['C', 'I']:
        return -1, -1

    return newX, newY

def melt(x, y, orientation, board):
    newX, newY = nextPosition(x, y, orientation)
    isIce = newX != -1 and newY != -1 and board[newY][newX] == 'I'
    if isIce:
        board[newY][newX] = '.'

    return isIce

def game():
    board = createBoard()
    moves = list(input())
    x = 0
    y = 7
    orientation = 1

    for move in moves:
        if move == 'F': 
            x, y = makeMove(x, y, orientation, board);
            if x == -1:
                print("Bug!")
                return
        elif move == 'R': 
            orientation += 1
            orientation %= 4
        elif move == 'L':
            orientation += 3
            orientation %= 4
        else: 
            state = melt(x, y, orientation, board)
            if not state: 
                print("Bug!")
                return

    if board[y][x] == 'D':
        print("Diamond!")
    else:
        print("Bug!")
            

game()

