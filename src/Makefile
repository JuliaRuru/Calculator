CC=gcc
CFLAG=-Wall -Wextra -Werror
APP=build/Calculator.app

all: uninstall clean install test

build:
	mkdir build
	cd ./build/ && qmake ../ && make

install: build
	mkdir $(HOME)/Desktop/Calculator/
	cp -rf $(APP) $(HOME)/Desktop/Calculator/
	make clean

run: uninstall clean install
	open $(HOME)/Desktop/Calculator/Calculator.app

uninstall:
	rm -rf ../Calculator/
	rm -rf $(HOME)/Desktop/Calculator/

dvi:
	makeinfo --html --no-warn --no-validate --force doc.texi
	open ./doc/index.html

check: test
	cp -f ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --filter=-runtime/printf --extensions=c *.c
	python3 ../materials/linters/cpplint.py --extensions=h calculator.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
	rm -rf CPPLINT.cfg
	CK_FORK=no leaks --atExit -- ./test

dist: clean
	mkdir dist/
	tar -cvzf Calculator.tgz *
	mv Calculator.tgz dist/

calculator.o:
	$(CC) $(CFLAG) -c calculator.c -o calculator.o

test_prepare: clean calculator.o
	$(CC) $(CFLAG) -c test.c -o test.o
	$(CC) test.o calculator.o -o test -lcheck

test: test_prepare
	./test

gcov_report: test_prepare
	$(CC) --coverage test.c -o test -lcheck calculator.c
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html

clean:
	rm -rf *.o *.gcda *.gcno *.info test report build test doc dist

rebuild: clean all
