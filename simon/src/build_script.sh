#!/bin/bash
export PATH=~/Pulpit/pebble-sdk/arm-cs-tools/bin:$PATH

echo -e "#define DISPLAY_SECONDS true\n#define HOUR_VIBRATION true\n#define LANG 0\n#define INVERTED false" > src/build_config.h
./waf clean build
mv build/simon.pbw builds/Simon_seconds_vibr.pbw
#sleep 1
echo -e "#define DISPLAY_SECONDS false\n#define HOUR_VIBRATION true\n#define LANG 0\n#define INVERTED false" > src/build_config.h
./waf clean build
mv build/simon.pbw builds/Simon_minute_vibr.pbw
#sleep 1
echo -e "#define DISPLAY_SECONDS true\n#define HOUR_VIBRATION false\n#define LANG 0\n#define INVERTED false\n" > src/build_config.h
./waf clean build
mv build/simon.pbw builds/Simon_seconds.pbw
#sleep 1
echo -e "#define DISPLAY_SECONDS false\n#define HOUR_VIBRATION false\n#define LANG 0\n#define INVERTED false\n" > src/build_config.h
./waf clean build
mv build/simon.pbw builds/Simon_minute.pbw
echo -e "#define DISPLAY_SECONDS true\n#define HOUR_VIBRATION true\n#define LANG 0\n#define INVERTED true" > src/build_config.h
./waf clean build
mv build/simon.pbw builds/Simon_seconds_vibr_inv.pbw
#sleep 1
echo -e "#define DISPLAY_SECONDS false\n#define HOUR_VIBRATION true\n#define LANG 0\n#define INVERTED true" > src/build_config.h
./waf clean build
mv build/simon.pbw builds/Simon_minute_vibr_inv.pbw
#sleep 1
echo -e "#define DISPLAY_SECONDS true\n#define HOUR_VIBRATION false\n#define LANG 0\n#define INVERTED true\n" > src/build_config.h
./waf clean build
mv build/simon.pbw builds/Simon_seconds_inv.pbw
#sleep 1
echo -e "#define DISPLAY_SECONDS false\n#define HOUR_VIBRATION false\n#define LANG 0\n#define INVERTED true\n" > src/build_config.h
./waf clean build
mv build/simon.pbw builds/Simon_minute_inv.pbw

