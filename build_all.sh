cd SFLCARS-utility
cmake ./
make
mv libsflcars-utility.so /usr/lib/libsflcars-utlity.so

cd ../
cd SFLCARS-interface
cmake ./
make
mv libsflcars-interface.so /usr/lib/libsflcars-interface.so
ln -s ../SFLCARS-interface/resources ../SFLCARS-main/resources

cd ../
cd SFLCARS-main
cmake ./
make

cd ../
cd SFLCARS-server
cmake ./
make

cd ../
cd SFLCARS-commandline
cmake ./
make

echo "build complete"
