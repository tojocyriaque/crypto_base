src= src/*.cpp
bin = bin/main
flags = -Wall -Wextra


exec:
	- clang++ $(src) -o $(bin) $(flags)
run:
	- $(bin)

clean:
	- rm $(bin)