#/bin/sh
# cmake --build . --target clean
cmake . -B build
cd build
cmake --build . || exit
echo ""
echo "---"
./Fuoco