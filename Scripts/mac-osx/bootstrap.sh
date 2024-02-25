 cd vendor/premake-core
make -f Bootstrap.mak macosx-clean
make -f Bootstrap.mak macosx

# Compile GLEW
cd ../../AlphaProject/vendor/GLEW/auto
make
cd ..
make
sudo make install
make clean

cd ../../..
# Use 
./vendor/premake-core/bin/release/premake5 --file=premake-macosx.lua gmake2