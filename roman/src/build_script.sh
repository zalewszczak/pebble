#!/bin/bash
export PATH=~/Pulpit/pebble-sdk/arm-cs-tools/bin:$PATH

langs=("$(cat src/lang.h | grep '^ * ' | cut -d " " -f 3)")

for num in $langs
do
    lang_num=$(grep " * $num " src/lang.h | cut -d ' ' -f 3)
    lang_name=$(grep " * $num " src/lang.h | cut -d ' ' -f 4)
    echo -e "#define DISPLAY_SECONDS true\n#define HOUR_VIBRATION true\n#define LANG $lang_num\n#define INVERTED false" > src/build_config.h
    ./waf clean build
    mv build/roman.pbw builds/Roman_seconds_vibr_$lang_name.pbw
    #sleep 1
    echo -e "#define DISPLAY_SECONDS false\n#define HOUR_VIBRATION true\n#define LANG $lang_num\n#define INVERTED false" > src/build_config.h
    ./waf clean build
    mv build/roman.pbw builds/Roman_minute_vibr_$lang_name.pbw
    #sleep 1
    echo -e "#define DISPLAY_SECONDS true\n#define HOUR_VIBRATION false\n#define LANG $lang_num\n#define INVERTED false" > src/build_config.h
    ./waf clean build
    mv build/roman.pbw builds/Roman_seconds_$lang_name.pbw
    #sleep 1
    echo -e "#define DISPLAY_SECONDS false\n#define HOUR_VIBRATION false\n#define LANG $lang_num\n#define INVERTED false" > src/build_config.h
    ./waf clean build
    mv build/roman.pbw builds/Roman_minute_$lang_name.pbw
    #sleep 1
    echo -e "#define DISPLAY_SECONDS true\n#define HOUR_VIBRATION true\n#define LANG $lang_num\n#define INVERTED true" > src/build_config.h
    ./waf clean build
    mv build/roman.pbw builds/Roman_seconds_vibr_inv_$lang_name.pbw
    #sleep 1
    echo -e "#define DISPLAY_SECONDS false\n#define HOUR_VIBRATION true\n#define LANG $lang_num\n#define INVERTED true" > src/build_config.h
    ./waf clean build
    mv build/roman.pbw builds/Roman_minute_vibr_inv_$lang_name.pbw
    #sleep 1
    echo -e "#define DISPLAY_SECONDS true\n#define HOUR_VIBRATION false\n#define LANG $lang_num\n#define INVERTED true" > src/build_config.h
    ./waf clean build
    mv build/roman.pbw builds/Roman_seconds_inv_$lang_name.pbw
    #sleep 1
    echo -e "#define DISPLAY_SECONDS false\n#define HOUR_VIBRATION false\n#define LANG $lang_num\n#define INVERTED true" > src/build_config.h
    ./waf clean build
    mv build/roman.pbw builds/Roman_minute_inv_$lang_name.pbw
    #sleep 1
done 
   
