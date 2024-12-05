
#!/bin/bash

. build.sh

if [ $COMPILE_STATUS -eq 0 ]; then
    $OUTPUT_FILE res/day02_input.txt
fi
