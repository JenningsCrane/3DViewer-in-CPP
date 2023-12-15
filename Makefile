CC=g++
CFLAGS=-std=c11 -Wall -Werror -Wextra -g -pedantic -D_GNU_SOURCE
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage
OS = $(shell uname)

ifeq ($(OS), Linux)
#-lsubunit
	CHECKFLAGS=-lpthread -lcheck -pthread -lrt -lm
else
	CHECKFLAGS=-lcheck -lm -lpthread
endif

all: clean install dist dvi check_style leaks clean

rebuild: clean all

install: uninstall
	mkdir build
	cp -rf 3D_Viewer.pro build
	cp -rf model build
	cp -rf controller build
	cp -rf view build
	cp -rf gif_library build
	cp -rf objects build
	cp -rf main.cc build
	cp -rf viewer_data.h build
	cd build && qmake 3D_Viewer.pro
	make -C build
	cd build && make clean
	open ./build/3D_Viewer.app/Contents/MacOS/3D_Viewer

uninstall:
	rm -rf build
	make clean

dvi:
	open ./dvi_readme/readme.txt

dist:
	tar -cvf build/3D_Viewer.tar build
	gzip build/3D_Viewer.tar
	mv build/3D_Viewer.tar.gz ./

test:
	cd tests && make

style:
	cp ../materials/linters/.clang-format ./
	clang-format -i ./main.cc
	clang-format -i ./view/*.cc
	clang-format -i ./view/*.h
	clang-format -i ./controller/*.cc
	clang-format -i ./controller/*.h
	clang-format -i ./model/*.cc
	clang-format -i ./model/*.h
	clang-format -i ./model/processing_file/*.cc
	clang-format -i ./model/processing_file/*.h
	clang-format -i ./model/rotation_strategy/*.cc
	clang-format -i ./model/rotation_strategy/*.h
	rm -rf .clang-format

check_style:
	cp ../materials/linters/.clang-format ./
	clang-format -n ./main.cc >> logfile.log
	clang-format -n ./view/*.cc >> logfile.log
	clang-format -n ./view/*.h >> logfile.log
	clang-format -n ./controller/*.cc >> logfile.log
	clang-format -n ./controller/*.h >> logfile.log
	clang-format -n ./model/*.cc >> logfile.log
	clang-format -n ./model/*.h >> logfile.log
	clang-format -n ./model/processing_file/*.cc >> logfile.log
	clang-format -n ./model/processing_file/*.h >> logfile.log
	clang-format -n ./model/rotation_strategy/*.cc >> logfile.log
	clang-format -n ./model/rotation_strategy/*.h >> logfile.log
	rm -rf .clang-format

leaks:
	cd tests && make leaks

clean:
	rm -rf *.o \
		*.a \
		*.app \
		*.so \
		*.gcno \
		*gcda \
		*.gcov \
		gcov_report.* \
		*.dSYM \
        RESULT_VALGRIND.txt \
		*.out \
        unit-test \
        vtests_run \
		run \
		gcov \
		report/ \
		gcov_report/ \
		report.info \
		gcov_report \
		gcov_test \
		tests/res_test \
		3D_Viewer.pro.user \
		3D_Viewer.tar.gz
