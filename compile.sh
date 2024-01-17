### bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

if clang -o foi.out src/main.c src/render.c src/point.c -lncurses;
then
	echo "\n${GREEN}Compile Successful${NC}\n"
	chmod +x foi.out
	./foi.out
else
	echo "\n${RED}Compile Failed${NC}\n"
fi