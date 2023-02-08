@echo off

if exist "Tic_Tac_Toe\bin" (
    RD /S /Q "Tic_Tac_Toe\bin"
)

MD "Tic_Tac_Toe\bin"

COPY "C:\Users\ismai\OneDrive\Desktop\Aiv_3\Aiv_3\SDL2.dll" "C:\Users\ismai\OneDrive\Desktop\Aiv_3\Aiv_3\Tic_Tac_Toe\bin\SDl2.dll"

clang -I.\SDL2-devel-2.26.0-VC\SDL2-2.26.0\include\ -o Tic_Tac_Toe\bin\main.exe .\Tic_Tac_Toe\src\logic.c .\Tic_Tac_Toe\src\rendering.c .\Tic_Tac_Toe\src\main.c .\Tic_Tac_Toe\src\SDL2_gfxPrimitives.c  -ITic_Tac_Toe\include -L.\SDL2-devel-2.26.0-VC\SDL2-2.26.0\lib\x64 -lSDL2 
.\Tic_Tac_Toe\bin\main.exe