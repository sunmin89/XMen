.PHONY: clean

#CROSS=/home/sunmin/bins/riscv/bin/riscv64-unknown-elf-
CROSS=~/bins/Xuantie-900-gcc-linux-5.10.4-glibc-x86_64-V2.6.1/bin/riscv64-unknown-linux-gnu-
CC=${CROSS}gcc
CFLAGS	= -std=c90 -Wall -fPIC -fno-stack-protector -DNOSTRUCTASSIGN
run: dry2 dry2nr dry2o
	#run under p550 rockos
	# ./dry2 20000000
	#run under qemu 
	# ~/bins/riscv/bin/qemu-riscv64ilp32 ./dry2 20000000
	~/bins/qemu-xuantie/bin/qemu-riscv64 -L ~/bins/Xuantie-900-gcc-linux-5.10.4-glibc-x86_64-V2.6.1/sysroot/ ./dry2nr 20000000
	# ./dry2nr ${1-50000} 2>/dev/null
	# ./dry2o ${1-50000} 2>/dev/null

dry2: dry.h dry1.c dry2.c
	${CC} -c ${CFLAGS} dry1.c -o dry1.o
	${CC} ${CFLAGS} dry2.c dry1.o ${LFLAGS} -o dry2 

dry2nr: dry.h dry1.c dry2.c
	${CC} -c -DREG ${CFLAGS} dry1.c -o dry1.o
	${CC} -DREG ${CFLAGS} dry2.c dry1.o ${LFLAGS} -o dry2nr

dry2o: dry.h dry1.c dry2.c
	${CC} -c -O ${CFLAGS} dry1.c -o dry1.o
	${CC} -O ${CFLAGS} dry2.c dry1.o ${LFLAGS} -o dry2o

clean:
	rm -f dry1.o dry2 dry2nr dry2o
