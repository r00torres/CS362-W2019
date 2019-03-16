CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

#Unit and card tests - Assignemnt 3
unittest1: dominion.o unittest1.c
	gcc -fprofile-arcs -ftest-coverage dominion.o unittest1.c rngs.c -o unittest1 -g $(CFLAGS)

unittest2: dominion.o unittest2.c
	gcc -fprofile-arcs -ftest-coverage dominion.o unittest2.c rngs.c -o unittest2 -g $(CFLAGS)

unittest3: dominion.o unittest3.c
	gcc -fprofile-arcs -ftest-coverage dominion.o unittest3.c rngs.c -o unittest3 -g $(CFLAGS)

unittest4: dominion.o unittest4.c
	gcc -fprofile-arcs -ftest-coverage dominion.o unittest4.c rngs.c -o unittest4 -g $(CFLAGS)

cardtest1: dominion.o cardtest1.c
	gcc -fprofile-arcs -ftest-coverage dominion.o cardtest1.c rngs.c assertTests.c -o cardtest1 -g $(CFLAGS)

cardtest2: dominion.o cardtest2.c
	gcc -fprofile-arcs -ftest-coverage dominion.o cardtest2.c rngs.c assertTests.c -o cardtest2 -g $(CFLAGS)

cardtest3: dominion.o cardtest3.c
	gcc -fprofile-arcs -ftest-coverage dominion.o cardtest3.c rngs.c assertTests.c -o cardtest3 -g $(CFLAGS)

cardtest4: dominion.o cardtest4.c
	gcc -fprofile-arcs -ftest-coverage dominion.o cardtest4.c rngs.c assertTests.c -o cardtest4 -g $(CFLAGS)

unittestresults: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1 &> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

#Random Card tests - Assignemnt 4
randomtestcard1: dominion.o randomtestcard1.c
	gcc -fprofile-arcs -ftest-coverage dominion.o randomtestcard1.c rngs.c assertTests.c -o randomtestcard1 -g $(CFLAGS)

randomtestcard2: dominion.o randomtestcard2.c
	gcc -fprofile-arcs -ftest-coverage dominion.o randomtestcard2.c rngs.c assertTests.c -o randomtestcard2 -g $(CFLAGS)

randomtestadventurer: dominion.o randomtestadventurer.c
	gcc -fprofile-arcs -ftest-coverage dominion.o randomtestadventurer.c rngs.c assertTests.c -o randomtestadventurer -g $(CFLAGS)

randomtestresults: randomtestcard1 randomtestcard2 randomtestadventurer
	./randomtestcard1 &> randomtestcard1.out
	gcov -b -f dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	./randomtestcard2 &> randomtestcard2.out
	gcov -b -f dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
	./randomtestadventurer &> randomtestadventurer.out
	gcov -b -f dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

testDom: unittestresults randomtestresults
	gcov -b -f dominion.c &> testcoverage.out
	cat dominion.c.gcov >> testcoverage.out

assertTests: assertTests.h assertTests.c
	gcc -o assertT assertTests.c -g $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out 
	rm -f testDrawCard testDrawCard.exe unittest1 unittest1.exe unittest2 unittest2.exe unittest3 unittest3.exe unittest4 unitttest4.exe
	rm -f cardtest1 cardtest1.exe cardtest2 cardtest2.exe cardtest3 cardtest3.exe cardtest4 cardtest4.exe
	rm -f randomtestadventurer randomtestadventurer.exe randomtestcard1 randomtestcard1.exe randomtestcard2 randomtestcard2.exe