#!/bin/bash
export PATH=~/Pulpit/pebble-sdk/arm-cs-tools/bin:$PATH

echo -e "#define DISPLAY_DATE false\n#define HOUR_VIBRATION true\n#define LANG 0\n#define INVERTED false" > src/build_config.h
./waf clean build
mv build/swiss.pbw builds/Swiss_vibr.pbw
#sleep 1
echo -e "#define DISPLAY_DATE false\n#define HOUR_VIBRATION false\n#define LANG 0\n#define INVERTED false" > src/build_config.h
./waf clean build
mv build/swiss.pbw builds/Swiss.pbw
#sleep 1
echo -e "#define DISPLAY_DATE false\n#define HOUR_VIBRATION true\n#define LANG 0\n#define INVERTED true" > src/build_config.h
./waf clean build
mv build/swiss.pbw builds/Swiss_vibr_inv.pbw
#sleep 1
echo -e "#define DISPLAY_DATE false\n#define HOUR_VIBRATION false\n#define LANG 0\n#define INVERTED true" > src/build_config.h
./waf clean build
mv build/swiss.pbw builds/Swiss_inv.pbw
#sleep 1

langs=("$(cat src/lang.h | grep '^ * ' | cut -d " " -f 3)")

for num in $langs
do
    lang_num=$(grep " * $num " src/lang.h | cut -d ' ' -f 3)
    lang_name=$(grep " * $num " src/lang.h | cut -d ' ' -f 4)
    echo -e "#define DISPLAY_DATE true\n#define HOUR_VIBRATION true\n#define LANG $lang_num\n#define INVERTED false" > src/build_config.h
    ./waf clean build
    mv build/swiss.pbw builds/Swiss_date_vibr_$lang_name.pbw
    #sleep 1
    echo -e "#define DISPLAY_DATE true\n#define HOUR_VIBRATION false\n#define LANG $lang_num\n#define INVERTED false" > src/build_config.h
    ./waf clean build
    mv build/swiss.pbw builds/Swiss_date_$lang_name.pbw
    #sleep 1
    echo -e "#define DISPLAY_DATE true\n#define HOUR_VIBRATION true\n#define LANG $lang_num\n#define INVERTED true" > src/build_config.h
    ./waf clean build
    mv build/swiss.pbw builds/Swiss_date_vibr_inv_$lang_name.pbw
    #sleep 1
    echo -e "#define DISPLAY_DATE true\n#define HOUR_VIBRATION false\n#define LANG $lang_num\n#define INVERTED true" > src/build_config.h
    ./waf clean build
    mv build/swiss.pbw builds/Swiss_date_inv_$lang_name.pbw
    #sleep 1
done 
   
