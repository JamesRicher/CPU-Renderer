#!/bin/zsh

find ./assets -maxdepth 1 -type f -name '*.obj' | while IFS= read -r line; do
    OBJ_FILENAME=${line:t}
    JSON_FILENAME=${OBJ_FILENAME/%.obj/.json}
    echo "Converting $OBJ_FILENAME to $JSON_FILENAME"
    ./build/src/tools/convert_mesh/ConvertMesh -o $OBJ_FILENAME -j $JSON_FILENAME 
done

