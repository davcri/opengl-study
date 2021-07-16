#/bin/sh
cmake --build . --target clean
cmake . -DUSE_MYMATH=ON
cmake --build .
./Fuoco