### bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

if cd target/
then
cd ..
else
echo "\ncreating ${RED}target/${NC} directory"
mkdir target
fi

if clang -o target/fluffy.out src/main.c src/render.c src/point.c src/plane.c src/core.c -lncurses
then
	echo "\n${GREEN}Compile Successful${NC}\n"
	chmod +x target/fluffy.out
	target/./fluffy.out
else
	echo "\n${RED}Compile Failed${NC}\n"
fi