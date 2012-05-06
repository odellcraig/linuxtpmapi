
#!/bin/sh
#This API or scripts talk about how to activate the TPM Module with tpm_tools  on Linux Kernel.
# Written by Suneetha Tedla 2012 04/27/2012
# it only tested and works on the following configuations and 
# The OS version is Ubuntu 11.10
# Linux  3.0.0-12-server 
# 20-Ubuntu UTC 2011 x86_64 x86_64 x86_64 GNU/Linux 
# This scripts talks only about how to activate the module tpm_tis.
# Assuming you have login into the server as root installed apt-get, aptitude package and running bash
# could able to download packages from the internet or repository of ubuntu 
# Make sure you have updated apt-get and chmod to activatetpm.sh
# This script has option of download the source code of trousers and tpm-tools from sourfoge.com on to gandalf.uccs.edu 
#If you are downloading them manually you can do that too but make sure to the way in advance on to this server or other
# you already placed all these scripts in your home directory on the server in my case (/home/csnet/)
# I downloaded tpm-tools-1.3.7.1.tar.gz trousers-0.3.8.tar.gz them to gandalf.uccs.edu to so I sued scp 
# in my case the user is csnet ( I used the lab from cs526 class)
# When you open configure files please remove CFLAGS -Werror and :wq! the file





# startup...

echo "Preparing the server"
echo
std_sleep() {
  sleep 10
}

ls -la /lib/modules/`uname -r`/kernel/drivers/char/tpm
echo " You are not seeing just as tpm that means you do not have access to tpm module"
std_sleep
sudo modprobe tpm_bios
sudo modprobe tpm
sudo modprobe tpm_tis force=1 interrupts=0
dmesg

echo "making sure you have access to tpm hardware module or any errors if you do not see somthing like this"
echo "tpm_tis tpm_tis: 1.2 TPM (device-id 0x4A10, rev-id 78"
echo "please control +c or exit"

echo
 
std_sleep

#apt-get update
apt-get install libssl-dev 

cd /home/csnet
mkdir tpm
cd ./tpm
scp stedla@gandalf.uccs.edu:*.gz .
tar -xzf tpm-tools-1.3.7.1.tar.gz
tar -xzf trousers-0.3.8.tar.gz
rm *.gz
ls -ltr
std_sleep
echo "You are about to configure, make and makeinstall for trousers"
cd trou*
std_sleep
echo "You need remove the -Werror from CFLAGS in ./configure due to bugs for trousers"
std_sleep
vi ./configure
mkdir insttools
cp /home/csnet/trousers-install.sh .
chmod 777 trousers-install.sh 
./trousers-install.sh
std_sleep
echo "You are about to configure, make and makeinstall for tpm-tools"
cd /home/csnet/tpm/tpm*
std_sleep
echo "You need remove the -Werror from CFLAGS in ./configure due to bugs for tpm-tools"
std_sleep
vi ./configure
mkdir insttools
cp /home/csnet/tpm-tool-install.sh .
chmod 777 tpm-tool-install.sh
./tpm-tool-install.sh
std_sleep
echo "You going to start the tcsd for tpm to see the device"
sudo /usr/local/sbin/tcsd start
sudo tcsd -f

std_sleep
echo "You going to see the version, I got error due to I tested on Ubuntu VM"
sudo ls -las /usr/local/sbin/
sudo /usr/local/sbin/tpm_version

std_sleep
echo "You going to see the taking tpm_takeownership, I got error due to I tested on Ubuntu VM"

sudo tpm_takeownership

std_sleep
echo "You going to see the taking tpm_createek, I got error due to I tested on Ubuntu VM"

sudo tpm_createek

std_sleep
echo "You going to see the taking tpm_getpubek, I got error due to I tested on Ubuntu VM"


sudo tpm_getpubek

echo "Installation complete."
echo "If you have problems with tpm-tools, please read the documentation first,"
echo "as many kinds of potential problems are explained there."


exit 0

