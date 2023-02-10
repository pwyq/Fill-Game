###
# @author      Yanqing Wu
# @email       meet.yanqing.wu@gmail.com
# @create date 2023-02-10 05:39:00
# @modify date 2023-02-10 05:39:23
# @desc build file
###

# cmake --build . --target clean
mkdir -p build
cmake -S . -B build
cd build
make

cd ..
./build/src/fillgame
#./build/test/test_main
