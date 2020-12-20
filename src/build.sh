python3 client.py
rm ../site/*
rm mizi
rm website.md

cd ../mizi/src/
sh build.sh
cp main ../../src/mizi

cd ../../src
g++ -std=c++11 -DDEBUG -Wall -Wpedantic -Wshadow -Wextra -g -Og main.cpp -o main
./main
./mizi
