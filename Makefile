CC = g++ -std=c++17

build:
	$(CC) model/*cc controller/*.cc model/processing_file/*h model/rotation_strategy/rotation_strategy.cc -o test
