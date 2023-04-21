set -ex
jar cvfm cpp.jar src/MANIFEST.MF -C out/production/jnidemo/ JNICpp.class
rm -rf build
mkdir build && cd build
cmake ..
cmake --build .
