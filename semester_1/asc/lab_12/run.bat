nasm module.asm -fwin32 -o module.obj
cl main.c /link module.obj
main.exe