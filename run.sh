#/bin/sh
# cmake --build . --target clean
cmake . -DUSE_MYMATH=ON -B build
cd build
cmake --build .

echo ""
echo "---"
./Fuoco