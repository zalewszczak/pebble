#!/bin/bash
export PATH=~/Pulpit/pebble-sdk/arm-cs-tools/bin:$PATH

langs=("$(cat src/lang.h | grep '^ * ' | cut -d " " -f 3)")

for num in $langs
do
    lang_num=$(grep " * $num " src/lang.h | cut -d ' ' -f 4)
    lang_name=$(grep " * $num " src/lang.h | cut -d ' ' -f 6)
    lang_order=$(grep " * $num " src/lang.h | cut -d ' ' -f 5)
    echo -e "#define LANG $lang_num\n#define ORDER $lang_order" > src/build_config.h
    ./waf clean build
    mv build/jellytime.pbw builds/Jellytime_$lang_name.pbw
    #sleep 1
done    
