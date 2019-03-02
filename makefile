src = src
build_dir = build
target = qmcdump
objects = $(build_dir)/main.o $(build_dir)/crypt.o
cc = g++ -std=c++17 -O3

all: $(build_dir) $(target)

$(build_dir):
	mkdir -p $(build_dir)

$(target): $(objects)
	$(cc) -o $(target) $(objects)

$(build_dir)/main.o: $(src)/main.cpp $(src)/crypt.h
	$(cc) -c $(src)/main.cpp -o $(build_dir)/main.o

$(build_dir)/crypt.o: $(src)/crypt.cpp $(src)/crypt.h
	$(cc) -c $(src)/crypt.cpp -o $(build_dir)/crypt.o

.PHONY: clean
clean:
	rm -rf $(build_dir) $(target)

install: all
	mv $(target) /usr/local/bin
