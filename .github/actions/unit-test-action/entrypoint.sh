#!/usr/bin/env bash
set -e
. $IDF_PATH/export.sh
cd test
idf.py build
cd build
esptool.py --chip esp32 merge_bin --fill-flash-size 4MB -o flash_image.bin @flash_args
/opt/qemu/bin/qemu-system-xtensa -nographic -no-reboot -machine esp32 -drive file=flash_image.bin,if=mtd,format=raw -serial file:output.log
results=$(grep -E '[[:digit:]]+ Tests [[:digit:]]+ Failures [[:digit:]]+ Ignored' output.log) || exit 1
echo "$results"
echo "$results" | grep -q '0 Failures' || exit 1
