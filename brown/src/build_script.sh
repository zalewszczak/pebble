#!/bin/bash
export PATH=~/Pulpit/pebble-sdk/arm-cs-tools/bin:$PATH

echo -e "#define DISPLAY_SECONDS true\n#define HOUR_VIBRATION true\n#define LANG 0\n#define INVERTED false" > src/build_config.h
./waf clean build
mv build/brown.pbw builds/Brown_seconds_vibr.pbw
#sleep 1
echo -e "#define DISPLAY_SECONDS false\n#define HOUR_VIBRATION true\n#define LANG 0\n#define INVERTED false" > src/build_config.h
./waf clean build
mv build/brown.pbw builds/Brown_minute_vibr.pbw
#sleep 1
echo -e "#define DISPLAY_SECONDS true\n#define HOUR_VIBRATION false\n#define LANG 0\n#define INVERTED false" > src/build_config.h
./waf clean build
mv build/brown.pbw builds/Brown_seconds.pbw
#sleep 1
echo -e "#define DISPLAY_SECONDS false\n#define HOUR_VIBRATION false\n#define LANG 0\n#define INVERTED false" > src/build_config.h
./waf clean build
mv build/brown.pbw builds/Brown_minute.pbw
#sleep 1
echo -e "#define DISPLAY_SECONDS true\n#define HOUR_VIBRATION true\n#define LANG 0\n#define INVERTED true" > src/build_config.h
./waf clean build
mv build/brown.pbw builds/Brown_seconds_vibr_inv.pbw
#sleep 1
echo -e "#define DISPLAY_SECONDS false\n#define HOUR_VIBRATION true\n#define LANG 0\n#define INVERTED true" > src/build_config.h
./waf clean build
mv build/brown.pbw builds/Brown_minute_vibr_inv.pbw
#sleep 1
echo -e "#define DISPLAY_SECONDS true\n#define HOUR_VIBRATION false\n#define LANG 0\n#define INVERTED true" > src/build_config.h
./waf clean build
mv build/brown.pbw builds/Brown_seconds_inv.pbw
#sleep 1
echo -e "#define DISPLAY_SECONDS false\n#define HOUR_VIBRATION false\n#define LANG 0\n#define INVERTED true" > src/build_config.h
./waf clean build
mv build/brown.pbw builds/Brown_minute_inv.pbw


