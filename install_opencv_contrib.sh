OPENCV_VERSION='3.4.3'

# 0. Uninstall Opencv
#sudo dpkg -r libopencv-dev
#sudo dpkg -r opencv

# 1. Update
sudo apt-get -y update
sudo apt-get -y upgrade
sudo apt-get -y autoremove

# 2. Dependencies
sudo apt-get install -y build-essential cmake
sudo apt-get install -y qt5-default libvtk6-dev
sudo apt-get install -y zlib1g-dev libjpeg-dev libwebp-dev libpng-dev libtiff5-dev libjasper-dev libopenexr-dev libgdal-dev
sudo apt-get install -y libdc1394-22-dev libavcodec-dev libavformat-dev libswscale-dev libtheora-dev libvorbis-dev libxvidcore-dev libx264-dev yasm libopencore-amrnb-dev libopencore-amrwb-dev libv4l-dev libxine2-dev
sudo apt-get install -y libtbb-dev libeigen3-dev
sudo apt-get install -y make

# Keep it in a folder:
mkdir opencv_and_contrib
cd opencv_and_contrib

# 3. Download OPENCV
sudo apt-get install -y unzip wget
wget https://github.com/opencv/opencv/archive/${OPENCV_VERSION}.zip
unzip ${OPENCV_VERSION}.zip
rm -rf ${OPENCV_VERSION}.zip
mv opencv-${OPENCV_VERSION} OpenCV

# 4. Download Contrib
wget https://github.com/opencv/opencv_contrib/archive/${OPENCV_VERSION}.zip
unzip ${OPENCV_VERSION}.zip
rm -rf ${OPENCV_VERSION}.zip
mv opencv_contrib-${OPENCV_VERSION} opencv_contrib

# 5. Build
cd OpenCV
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DWITH_QT=ON -DWITH_OPENGL=ON -DFORCE_VTK=ON -DWITH_TBB=ON -DWITH_GDAL=ON -DWITH_XINE=ON -DBUILD_EXAMPLES=ON -DWITH_CUDA=ON -DENABLE_FAST_MATH=ON -DCUDA_FAST_MATH=ON -DWITH_CUBLAS=ON -DENABLE_PRECOMPILED_HEADERS=OFF -DOPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules ..
make -j4
sudo make install
sudo ldconfig
cd ../..

# verify: 
# pkg-config --modversion opencv
