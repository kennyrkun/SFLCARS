cd SFLCARS-utility
cmake ./
make
mv libsflcars-utility.so ../SFLCARS-main/libsflcars-utility.so

cd ../
cd SFLCARS-interface
cmake ./
make
mv libsflcars-interface.so ../SFLCARS-main/libsflcars-interface.so
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
