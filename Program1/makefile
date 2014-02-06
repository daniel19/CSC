boot1: boot1.asm boot2
	nasm -l boot1.list -DENTRY=`./getaddr.sh main`
boot2: boot2.exe
	objcopy -S -O binary boot2.exe boot2
boot2.exe: boot2_S.o boot2_c.o
	ld -g -Ttext 0x10000 -e main -o boot2.exe boot2_S.o boot2_c.o
boot2_c.o: boot2.c
	gcc -g -c -o boot2_c.o boot2.c
boot2_S.o: boot2.S
	gcc -g -c -masm=intel -o boot2_S.o boot2.S

clean:
	rm -rf *o boot2
	rm -rf *o boot1
