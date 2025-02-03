#include <iostream>
#include <thread>
#include <vector>
using namespace std;

#include <stdio.h>
#include <windows.h>

int nScreenWidth = 80;
int nScreenHeight = 30;
wstring tetromino [7];
int nFieldWidth = 12;
int nFieldHeight = 18;
unsigned char *pField = nullptr;

int Rotate(int px, int py, int r)
{
    int pi = 0;
    switch (r % 4)
    {
     case 0:
            pi = py * 4 + px;
            break;                  //0 degrees
     case 1:
            pi = 12 + py - (px * 4);
            break;                  //90 degrees
     case 2:
            pi = 15 - (py * 4) - px;
            break;                   //180 degrees
     case 3:
            pi = 3 - py + (px * 4);
            break;                  //270 degrees
    }
    return pi;
}

bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY)
{
    for(int px = 0; px < 4; px++)
        for(int py = 0; py < 4; py++)
        {
            //get index into piece
            int pi = Rotate(px, py, nRotation);

            //get index into field
            int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

            // Check that test is in bounds. Note out of bounds does
			// not necessarily mean a fail, as the long vertical piece
			// can have cells that lie outside the boundary, so we'll
			// just ignore them
            if (nPosX + px >= 0 && nPosX + px < nFieldWidth)
            {
                if (nPosY + py >= 0 && nPosY + py < nFieldHeight)
                {
                    if(tetromino[nTetromino][pi] != L'.' && pField[fi] != 0)
                        return false;//fail on first hit
                }
            }
        }
    return true;
}

int main ()
{
    wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight];
    for (int i = 0; i < nScreenWidth*nScreenHeight; i++) screen[i] = L' ';
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0 , NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    //creatre assets
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");

    tetromino[1].append(L"..X.");
    tetromino[1].append(L".XX.");
    tetromino[1].append(L".X..");
    tetromino[1].append(L"....");

    tetromino[2].append(L".X..");
    tetromino[2].append(L".XX.");
    tetromino[2].append(L"..X.");
    tetromino[2].append(L"....");

    tetromino[3].append(L"....");
    tetromino[3].append(L".XX.");
    tetromino[3].append(L".XX.");
    tetromino[3].append(L"....");

    tetromino[4].append(L"..X.");
    tetromino[4].append(L".XX.");
    tetromino[4].append(L"..X.");
    tetromino[4].append(L"....");

    tetromino[5].append(L"....");
    tetromino[5].append(L".XX.");
    tetromino[5].append(L"..X.");
    tetromino[5].append(L"..X.");

    tetromino[6].append(L"....");
    tetromino[6].append(L".XX.");
    tetromino[6].append(L".X..");
    tetromino[6].append(L".X..");

    pField = new unsigned char[nFieldWidth*nFieldHeight];// Create playfield buffer
    for (int x = 0; x < nFieldWidth; x++)// Board Boundary
        for(int y = 0; y < nFieldHeight; y++)
            pField[y*nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;
   
    
    bool bGameOver = false;

    while (!bGameOver)
    {
        //Game Timing ============================================

        //input ==================================================

        //game logic==============================================

        //Render Outpout

        //Draw Field
        for (int x = 0; x < nFieldWidth; x++)
            for (int y = 0; y < nFieldHeight; y++)
                screen[(y + 2)*nScreenWidth + (x + 2)] = L" ABCDEFG=#"[pField[y*nFieldWidth + x]];
        
        //Display Frame
        WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth*nScreenHeight, { 0,0 }, &dwBytesWritten);
    }

         

    return 0;
}