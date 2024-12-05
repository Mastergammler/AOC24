
#!/bin/bash

SOURCE_FILE="src/day02.cpp"
OUTPUT_DIR=".build"
export OUTPUT_FILE="$OUTPUT_DIR/d02"

OPTIONS="-std=c++03 -Wall -Wno-c++11-extensions"

T_START=$(date +%s%N)

clang++ $SOURCE_FILE -o $OUTPUT_FILE $OPTIONS
export COMPILE_STATUS=$?

T_END=$(date +%s%N)

CST_NANO_TO_MS=1000000
T_ELAPSED=$(((T_END - T_START)/ $CST_NANO_TO_MS))

if [ $COMPILE_STATUS -eq 0 ]; then

    echo "************************"
    echo "   Compile :: $T_ELAPSED ms "
    echo "************************"
fi

