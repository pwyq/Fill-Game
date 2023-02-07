# cmake --build . --target clean
mkdir -p build
cmake -S . -B build
cd build
make

cd ..
cp ./build/src/fillgame .

#time ./fillgame 1.*.3 1
#time ./fillgame 13*.3 1
#time ./fillgame .....*.....*.....*..... 1
#time ./fillgame 33213*2..33*44.22*33314*2244. 1

./build/test/test_main

#./fillgame 1.*33 1
