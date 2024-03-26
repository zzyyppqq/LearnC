echo '--- main_c execute --'
adb push ./cmake-build-debug/main_c /data/local/tmp
adb shell /data/local/tmp/main_c

echo '--- main_cpp execute --'
adb push ./cmake-build-debug/main_cpp /data/local/tmp
adb shell /data/local/tmp/main_cpp
