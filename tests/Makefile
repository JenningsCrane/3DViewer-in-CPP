CC = gcc -Wall -Werror -Wextra -std=c++17
LC = -lgtest -lgtest_main -lstdc++

all: test

tar:
	tar -czf object_files/obj.tar.gz object_files/*.obj

untar:
	tar -xzf object_files/obj.tar.gz

test: untar
	$(CC) *.cc ../model/*.cc ../model/rotation_strategy/*.cc ../model/processing_file/*.cc -o ./res_test $(LC)
	./res_test

# test_open_file:
# 	$(CC) ../model/processing_file/*.cc parcer_test.cc -o ./open_file_test $(LC)

leaks:
	CK_FORK=no leaks --atExit -- ./res_test

# 	./open_file_test

build: all

rebuild: clean build

clear: clean

clean:
	rm -rf *.out
	rm -rf *.obj
	rm -rf open_file_test
