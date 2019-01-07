sudo apt -y install update
sudo apt -y install upgrade
sudo apt-get -y install curl
sudo apt-get -y install libraw1394-11 libavcodec57 libavformat57 libswscale4 libswresample2 libavutil55 libgtkmm-2.4-1v5 libglademm-2.4-1v5 libgtkglextmm-x11-1.2-0v5 libgtkmm-2.4-dev libglademm-2.4-dev libgtkglextmm-x11-1.2-dev libusb-1.0-0

curl --output flycap.tgz --location https://eu.ptgrey.com/support/downloads/11156/
tar zxvf flycap.tgz
rm flycap.tgz
cd flycapture2-2.13.3.31-amd64/
sudo sh install_flycapture.sh

