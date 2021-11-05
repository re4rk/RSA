CC = gcc

RSA: main.o BigNumber.o RSA_test.o
	${CC} -o RSA.out main.o BigNumber.o RSA_test.o
	rm -rf ./*.o
	
main.o: main.c
	${CC} -c -o main.o main.c

BigNumber.o: BigNumber.c
	${CC} -c -o BigNumber.o BigNumber.c

RSA_test.o: RSA_test.c
	${CC} -c -o RSA_test.o RSA_test.c

clean :
	rm -rf ./*.o RSA.out

ran :
	rm -rf  ./rand* 