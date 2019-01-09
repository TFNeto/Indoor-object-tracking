# Requirements
- OpenCV
    - sh install_opencv_contrib.sh
- Flycapture
    - sh install_flycapture.sh
- [Qt Creator](https://www.qt.io/download)
- Boost lib
  - sudo apt install libboost-all-dev
Note: These we only tested on Ubuntu 18.04 LTS and Mint (?)

# Network config

To setup your network interface to use GigE cameras, run ifconfig and find the
network adapter that you intend to use the cameras on (eg. enp15s0):

`$ ifconfig`

Then, open up **/etc/network/interfaces** in a text editor (as sudo):

`$ sudo gedit /etc/network/interfaces`

and add the following lines (change enp15s0 to match the one shown in ifconfig):

```
iface enp15s0 inet static
address 169.254.0.64
netmask 255.255.0.0
mtu 9000

auto enp15s0
```

If using multiple interfaces, ensure that the addresses used are on different subnets
(eg. 169.254.0.64 and 169.253.0.64).
After closing the editor, it is recommended to reboot the computer before using
any GigE cameras.

If you are running Ubuntu, you'll also have to add the following lines to **/etc/sysctl.conf**:

```
net.core.rmem_max=1048576
net.core.rmem_default=1048576
```

Reload after changes:

`$ sudo sysctl -p`

Source: Readme from spinnaker-1.19.0.22-amd64 package


## Tested on Ubuntu 18.04