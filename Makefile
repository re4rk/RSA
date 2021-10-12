CC = gcc

app.out: main.o BigNumber.o
	${CC} -o app.out main.o BigNumber.o
	
main.o: main.c
	${CC} -c -o main.o main.c

BigNumber.o: BigNumber.c
	${CC} -c -o BigNumber.o BigNumber.c

clean :
	rm -rf ./*.o app.out

ran :
	rm -rf  ./rand*