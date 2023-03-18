###
# @author      Yanqing Wu
# @email       meet.yanqing.wu@gmail.com
# @create date 2023-02-10 05:39:00
# @modify date 2023-03-15 13:30:50
# @desc build file
###

# Flag to build Qt GUI.
IS_GUI=0

while [ True ]; do
if [ "$1" = "--gui" -o "$1" = "-g" ]; then
    IS_GUI=1
    shift 1
elif [ "$1" = "--cli" -o "$1" = "-c" ];then
    IS_GUI=0
    shift1
# elif [ "$1" = "--config" -o "$1" = "-c" ]; then
#     CONFIG=$2
#     shift 2
else
    break
fi
done

## update qrc; only for GUI
if [ $IS_GUI -eq 1 ]; then
    if [[ "$(python3 -V)" =~ "Python 3" ]]; then
        echo "python3 is installed"
    else
        echo "python3 is NOT installed"
        exit 1
    fi
    python3 ./generate_qrc.py > fillgame.qrc
fi

## build
# cmake --build . --target clean
mkdir -p build
if [ $IS_GUI -eq 1 ]; then
    cmake -DIS_BUILD_GUI:BOOL=ON -S . -B build
else
    cmake -DIS_BUILD_GUI:BOOL=OFF -S . -B build
fi
cd build
make

## move the executable to the root folder
cd ..
if [ -f ./build/src/fillgame_gui ]; then
    mv ./build/src/fillgame_gui .
elif [ -f ./build/src/fillgame_cli ]; then
    mv ./build/src/fillgame_cli .
fi
mv ./build/test/test_main .
