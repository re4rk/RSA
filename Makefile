CC = gcc -g -Wall

RSA: main.o BigNumber.o RSA_test.o
	${CC} -o RSA.out obj/main.o obj/BigNumber.o obj/RSA_test.o
	
main.o: src/main.c
	${CC} -c -o obj/main.o src/main.c

BigNumber.o: src/BigNumber.c
	${CC} -c -o obj/BigNumber.o src/BigNumber.c

RSA_test.o: src/RSA_test.c
	${CC} -c -o obj/RSA_test.o src/RSA_test.c

clean :
	rm -rf ./obj/* ./tmp/*
