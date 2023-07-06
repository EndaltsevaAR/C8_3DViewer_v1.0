CC=gcc
CFLAGS=-Wall -Wextra -std=c11
TST_CFLAGS:= -g $(CFLAGS) # -g для дебаггера на валгринде
GCOV_FLAGS=-fprofile-arcs -ftest-coverage #-fprpfile-arcs для сохранения статистики исполнения строк исходного файла, -ftest-coverage для записи статистики условных переходов (ветвлений).
LINUX_FLAGS=-lsubunit -lrt -lpthread -lm
LIBS=-lcheck
VALGRIND_FLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose

TARGET=s21_viewer.a # архив созданный утилитой ar из объектных файлов.

SRC=$(wildcard s21_*.c) # все файлы с разрешением .с
OBJ=$(patsubst %.c,%.o, ${SRC})

TEST_SRC=test.c

OS := $(shell uname -s)
USERNAME=$(shell whoami)

ifeq ($(OS),Linux)
  	OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

all: test gcov_report clean
install:
	make clean
	mv Makefile cloneMake && qmake && make && make clean && mv cloneMake Makefile
	make clean

uninstall:
	make clean
	rm -f 3d_Viewer
	rm -rf Dist_Viewer.tgz

dvi:
	open ./viewer.html

dist: install
	rm -rf Dist_Viewer/
	mkdir Dist_Viewer/
	mkdir Dist_Viewer/src
	mv 3d_Viewer Dist_Viewer/src/
	tar cvzf Dist_Viewer.tgz Dist_Viewer/
	rm -rf Dist_Viewer/


$(TARGET): ${SRC}
	gcc -c $(CFLAGS) $(SRC)
	ar rc $@ $(OBJ)
	ranlib $@
	cp $@ lib$@
	make clean_obj

test: $(TARGET)
ifeq ($(OS), Darwin)
	gcc $(CFLAGS) ${TEST_SRC} $< -o unit_test $(LIBS)
else
	gcc $(CFLAGS) ${TEST_SRC} $< -o unit_test $(LIBS) $(LINUX_FLAGS)
endif
	./unit_test

gcov_report: clean_test
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) ${TEST_SRC} ${SRC} -o test $(LIBS)
else
	$(CC) $(CFLAGS) $(GCOV_FLAGS) ${TEST_SRC} ${SRC} -o test $(LIBS) $(LINUX_FLAGS)
endif
	./test
	lcov -t "stest" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	$(OPEN_CMD) ./report/index.html

valgrind: $(TARGET)
	$(CC) $(TST_CFLAGS) ${TEST_SRC} $< -o test $(LIBS) $(LINUX_FLAGS)
	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./test

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -i *.c *.h *.cpp
	clang-format -style=Google -n *.c *.h *.cpp
	rm .clang-format

brsw:
	eval "$(/opt/goinfre/$(USERNAME)/homebrew/bin/brew shellenv)"
	brew update --force --quiet
	chmod -R go-w "$(brew --prefix)/share/zsh"

install_brew:
	cd /opt/goinfre/$(USERNAME)
	mkdir homebrew
	git clone https://github.com/Homebrew/brew homebrew
	make brsw

lcov:
	brew install lcov

clean_obj:
	rm -rf *.o

clean_lib:
	rm -rf *.a

clean_test:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf test
	rm -rf report

clean: clean_lib clean_lib clean_test clean_obj
	rm -rf unit_test
	rm -rf RESULT_VALGRIND.txt
	rm -rf .qmake.stash

rebuild: clean uninstall all

reinstall: clean uninstall install