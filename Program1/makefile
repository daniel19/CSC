boot1: boot1.asm boot2
boot2: boot2.exe
boot2.exe: boot2_S.o boot2_c.o
	ld -g -Ttext 0x10000 -e main -o boot2.exe boot2_S.o boot2_c.o
boot2_S.o: boot2.S
	gcc -g -c -masm=intel -o boo2_S.o boot2.S
boot2_c.0: boot2.c
	gcc -g -c -o boot2_c.o boot2.c
