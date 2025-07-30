#!/usr/bin/env bash
chmod +x "$0"
set -e
. $IDF_PATH/export.sh

idf.py build
cd build
esptool.py --chip esp32s3 merge_bin --fill-flash-size 4MB -o flash_image.bin @flash_args
cd ..
/opt/qemu/bin/qemu-system-xtensa -nographic -no-reboot -machine esp32s3 -drive file=build/flash_image.bin,if=mtd,format=raw -serial mon:stdio | tee output.log

results=$(grep -E '[[:digit:]]+ Tests [[:digit:]]+ Failures [[:digit:]]+ Ignored' output.log) || exit 1

echo "========================== Unit Test Results =========================="
echo "$results"
echo "======================================================================="
echo "$results" | grep -q '0 Failures' || exit 1
