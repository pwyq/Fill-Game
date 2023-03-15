###
# @author      Yanqing Wu
# @email       meet.yanqing.wu@gmail.com
# @create date 2023-02-10 05:39:00
# @modify date 2023-02-11 11:28:33
# @desc build file
###

## update qrc
if [[ "$(python3 -V)" =~ "Python 3" ]]; then
    echo "python3 is installed"
else
    echo "python3 is NOT installed"
    exit 1
fi
python3 ./generate_qrc.py > fillgame.qrc

## build
# cmake --build . --target clean
mkdir -p build
cmake -S . -B build
cd build
make

## run
cd ..
if [ -f ./build/src/fillgame_gui ]; then
    mv ./build/src/fillgame_gui .
elif [ -f ./build/src/fillgame_cli ]; then
    mv ./build/src/fillgame_cli .
fi
