#!/usr/bin/env bash
set -e
. $IDF_PATH/export.sh

# chmod -R a+w /github/workspace || true

cd test
idf.py build
cd build
esptool.py --chip esp32s3 merge_bin --fill-flash-size 4MB -o flash_image.bin @flash_args
cd ..
/opt/qemu/bin/qemu-system-xtensa -nographic -no-reboot -machine esp32s3 -drive file=build/flash_image.bin,if=mtd,format=raw -serial file:output.log

echo "========================== QEMU Serial Output =========================="
cat output.log
echo "======================================================================="

results=$(grep -E '[[:digit:]]+ Tests [[:digit:]]+ Failures [[:digit:]]+ Ignored' output.log) || exit 1

if command -v ruby >/dev/null && [ -f /opt/Unity-2.5.2/auto/parse_output.rb ]; then
    ruby /opt/Unity-2.5.2/auto/parse_output.rb -xml output.log || true
    [ -f report.xml ] && mv report.xml /github/workspace
fi

echo "========================== Unit Test Results =========================="
echo "$results"
echo "======================================================================="
echo "$results" | grep -q '0 Failures' || exit 1
