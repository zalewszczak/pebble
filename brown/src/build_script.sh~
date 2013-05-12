#!/bin/bash
export PATH=~/Pulpit/pebble-sdk/arm-cs-tools/bin:$PATH

echo -e "#define DISPLAY_SECONDS true\n#define HOUR_VIBRATION true\n#define LANG 0\n#define INVERTED false\n#define DISPLAY_DATE_ANALOG true" > src/build_config.h
./waf clean build
mv build/modern.pbw builds/Modern_seconds_vibr_analog.pbw
#sleep 1
echo -e "#define DISPLAY_SECONDS false\n#define HOUR_VIBRATION true\n#define LANG 0\n#define INVERTED false\n#define DISPLAY_DATE_ANALOG true" > src/build_config.h
./waf clean build
mv build/modern.pbw builds/Modern_minute_vibr_analog.pbw
#sleep 1
echo -e "#define DISPLAY_SECONDS true\n#define HOUR_VIBRATION false\n#define LANG 0\n#define INVERTED false\n#define DISPLAY_DATE_ANALOG true" > src/build_config.h
./waf clean build
mv build/modern.pbw builds/Modern_seconds_analog.pbw
#sleep 1
echo -e "#define DISPLAY_SECONDS false\n#define HOUR_VIBRATION false\n#define LANG 0\n#define INVERTED false\n#define DISPLAY_DATE_ANALOG true" > src/build_config.h
./waf clean build
mv build/modern.pbw builds/Modern_minute_analog.pbw

langs=("$(cat src/lang.h | grep '^ * ' | cut -d " " -f 3)")

for num in $langs
do
    lang_num=$(grep " * $num " src/lang.h | cut -d ' ' -f 3)
    lang_name=$(grep " * $num " src/lang.h | cut -d ' ' -f 4)
    echo -e "#define DISPLAY_SECONDS true\n#define HOUR_VIBRATION true\n#define LANG $lang_num\n#define INVERTED false\n#define DISPLAY_DATE_ANALOG false" > src/build_config.h
    ./waf clean build
    mv build/modern.pbw builds/Modern_seconds_vibr_$lang_name.pbw
    #sleep 1
    echo -e "#define DISPLAY_SECONDS false\n#define HOUR_VIBRATION true\n#define LANG $lang_num\n#define INVERTED false\n#define DISPLAY_DATE_ANALOG false" > src/build_config.h
    ./waf clean build
    mv build/modern.pbw builds/Modern_minute_vibr_$lang_name.pbw
    #sleep 1
    echo -e "#define DISPLAY_SECONDS true\n#define HOUR_VIBRATION false\n#define LANG $lang_num\n#define INVERTED false\n#define DISPLAY_DATE_ANALOG false" > src/build_config.h
    ./waf clean build
    mv build/modern.pbw builds/Modern_seconds_$lang_name.pbw
    #sleep 1
    echo -e "#define DISPLAY_SECONDS false\n#define HOUR_VIBRATION false\n#define LANG $lang_num\n#define INVERTED false\n#define DISPLAY_DATE_ANALOG false" > src/build_config.h
    ./waf clean build
    mv build/modern.pbw builds/Modern_minute_$lang_name.pbw
    #sleep 1
    echo -e "#define DISPLAY_SECONDS true\n#define HOUR_VIBRATION true\n#define LANG $lang_num\n#define INVERTED true\n#define DISPLAY_DATE_ANALOG false" > src/build_config.h
    ./waf clean build
    mv build/modern.pbw builds/Modern_seconds_vibr_inv_$lang_name.pbw
    #sleep 1
    echo -e "#define DISPLAY_SECONDS false\n#define HOUR_VIBRATION true\n#define LANG $lang_num\n#define INVERTED true\n#define DISPLAY_DATE_ANALOG false" > src/build_config.h
    ./waf clean build
    mv build/modern.pbw builds/Modern_minute_vibr_inv_$lang_name.pbw
    #sleep 1
    echo -e "#define DISPLAY_SECONDS true\n#define HOUR_VIBRATION false\n#define LANG $lang_num\n#define INVERTED true\n#define DISPLAY_DATE_ANALOG false" > src/build_config.h
    ./waf clean build
    mv build/modern.pbw builds/Modern_seconds_inv_$lang_name.pbw
    #sleep 1
    echo -e "#define DISPLAY_SECONDS false\n#define HOUR_VIBRATION false\n#define LANG $lang_num\n#define INVERTED true\n#define DISPLAY_DATE_ANALOG false" > src/build_config.h
    ./waf clean build
    mv build/modern.pbw builds/Modern_minute_inv_$lang_name.pbw
    #sleep 1
done 
   
