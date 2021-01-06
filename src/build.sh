pip --version
pip install telethon
pip install pandas
python3 extparse.py

rm ../site/*
rm mizi
rm website.md

# Need to move to mizi/src to build
cd ../mizi/src
sh build.sh
cp mizi ../../src/mizi

# Move back to link pump src
cd ../../src/
g++ -std=c++11 -DDEBUG -Wall -Wpedantic -Wshadow -Wextra -g -Og main.cpp -o linkpump

# Link pump generates website.md
./linkpump
# Run mizi
./mizi
