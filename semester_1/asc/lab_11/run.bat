nasm -fobj module.asm
nasm -fobj main.asm
alink main.obj module.obj -oPE -subsys console -entry start
main.exe