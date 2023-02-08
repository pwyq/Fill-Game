# cmake --build . --target clean
#export CMAKE_PREFIX_PATH=/home/pwyq/Qt5.12.8/5.12.8/gcc_64
#export CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:/usr/include/x86_64-linux-gnu/qt5
mkdir -p build
cmake -S . -B build
cd build
make

cd ..
./build/src/fillgame

#time ./fillgame 1.*.3 1
#time ./fillgame 13*.3 1
#time ./fillgame .....*.....*.....*..... 1
#time ./fillgame 33213*2..33*44.22*33314*2244. 1

#./build/test/test_main

#./fillgame 1.*33 1
