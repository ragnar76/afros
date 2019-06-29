                                                 / \  |  ___|  _ \ / _ \/ ___| 
                                                / _ \ | |_  | |_) | | | \___ \ 
                                               / ___ \|  _| |  _ <| |_| |___) |
                                              /_/   \_\_|   |_| \_\\___/|____/ 
                                             Atari/ARAnyM FRee Operating System

AFROS is a self-explanatory acronym: Atari FRee Operating System. It used to be distributed in the form of a harddisk image but now it's just a plain set of files creating preinstalled TOS compatible EmuTOS/FreeMiNT/fVDI/XaAES based operating system. The most exciting feature is its completely Free nature - all key components (EmuTOS, FreeMiNT, fVDI, XaAES and Teradesk) are completely free "as in Freedom" and can be redistributed under the GNU General Public License. This is the first time for Atari users to have a TOS/GEM compatible, complete, free and powerful operating system - from power-on all the way through to the multitasking GEM desktop with robust FreeMiNT kernel in the background and fast fVDI graphics on the screen.

Although AFROS contains software generally available for all Atari/TOS compatible platforms it's been optimized to be powered by the ARAnyM. Thus AFROS contains up-to-date NatFeat based hardware drivers for video, disk, sound, HostFS and networking and so is suitable also for updating your regular ARAnyM setup with fresh ARAnyM drivers.

In the combination of ARAnyM/Linux and AFROS you basically get a completely free TOS/MiNT compatible operating system running on any machine where Linux runs. That's a break-through for all Atari users - now you can turn almost any hardware into your familiar TOS/GEM system 

This is the first truly Free OS compatible with TOS/GEM on Atari computers.

- Built using Free Software - OS kernel, VDI+AES and applications
- Always the latest and greatest versions of used components
- Ready to use GEM desktop with text editor, calculator and more utils
- Internet enabled (web browser, ftp client, mail agent, VNC viewer)
- Multimedia enhanced (view images, listen to music, watch movies)
- Preconfigured for ARAnyM but can be used on any Atari/compatible

AFROS was created and is brought to you by Petr Stehlik
Visit http://aranym.org/afros 

This copy is maintained by ragnar <ragnar76@riseup.net>

This wouldn't be possible without great work of the following projects that release their software under the GPL or other Free licenses:

- EmuTOS - a free TOS replacement (http://emutos.sf.net/)
- FreeMiNT - a free multitasking others (http://www.freemint.de/)
- fVDI - a free/fast VDI (http://www.klockars.net/)
- XaAES - a free multitasking AES (http://xaaes.atariforge.net/)
- TeraDesk - a free desktop replacement (http://solair.eunet.yu/~vdjole/)
- HighWire - a free Html/Web browser (http://highwire.atari-users.net/)

and of course ARAnyM, the virtual machine for TOS/GEM 16/32-bit applications.

Please note that AFROS now contains much more software to create a full featured Atari desktop. All the software is free to distribute though their licences vary from freeware to PostCardware.

Also, many of the programs included here are multilingual (EmuTOS, Teradesk, Aniplayer and others) but I have configured everything for English users and removed other languages support. Feel free to download the full archives and configure them to language of your choice.

## How to start it:
Unpack it anywhere. Then start ARAnyM from within the unpacked 'afros' folder with the provided config file:

    user:~/afros$ aranym -c config

There is a batch file for MS-Windows users that works out-of-the-box if the afros folder is inside of your ARAnyM installation folder (i.e. the aranym.exe is next to the afros folder). Simply start the aranym.bat.

How to use it:
-
AFROS can be used for updating your regular ARAnyM/Atari software setup: if you use a disk image then set up your disk on the IDE channel and then copy the FreeMiNT operating system, fVDI and their drivers to appropriate locations in your setup. You'll want to update the following stuff at least:

- AUTO\FVDI.PRG and its GEMSYS\ARANYM.SYS driver and \FVDI.SYS config file

If you update MINT.PRG you must update also the MINT folder contents - you might want to update also the TOS drivers found in the AUTO folder

If you don't use disk image anymore you can simply copy the updated driver files in your host operating system since this AFROS release no longer uses disk image thus all files are easily accessible. Check the "drive_c" folder to see all the files there.

## How to set it up:
AFROS tries to set up networking but it's not fully automatic - you need to  configure few things by yourself:

1) ARAnyM config, section [ETH0]: set up your type (p-t-p or bridge), device (tap0 or higher) and mainly the IP addresses - Atari IP is the AFROS IP, Host IP is the network gateway, and also Netmask.

2) DNS IP address - enter your DNS IP in "drive_c/etc/resolv.conf" file (replace the value that is there now)
    $ grep nameserver /etc/resolv.conf  > drive_c/etc/resolv.conf 

3) make sure your host networking is working and TUN/TAP is configured properly (read the ARAnyM documentation for detailed information)

### Debian/Ubuntu network setup:
An important note! Something has changed in Debian 8 and upwards. You have to select the legacy version of iptables first. This can be done by entering the following command:

      update-alternatives –config iptables

The Change is instant and you can continue to configure your system

Before you start, you need to install tun/tap drivers first. This can be done by entering the following command:

      sudo apt-get install bridge-utils uml-utilities

For running on a Debian/Ubuntu based system with networking enabled please add the following section to your /etc/network/interfaces file:

      auto tap0
      iface tap0 inet static
      address 192.168.251.1
      pointopoint 192.168.251.2
      netmask 255.255.255.255
      tunctl_user YOUR_LOGIN_NAME
      up iptables -t nat -A POSTROUTING -s 192.168.251.2 -j MASQUERADE
      down iptables -t nat -D POSTROUTING -s 192.168.251.2 -j MASQUERADE
      up echo 1 > /proc/sys/net/ipv4/ip_forward

Don't forget to replace the YOUR_LOGIN_NAME with your login name. Then restart the networking with "sudo /etc/init.d/networking restart".

### Generic Linux network setup:
Enter the following commands in a shell as root, replace YOUR_LOGIN_NAME with the user's login name that will be starting the ARAnyM (i.e. yours)

      modprobe tun
      chown YOUR_LOGIN_NAME /dev/net/tun
      sleep 1
      tunctl -t tap0 -u YOUR_LOGIN_NAME
      sleep 1
      ifconfig tap0 192.168.251.1 pointopoint 192.168.251.2 netmask 255.255.255.255 up
      iptables -t nat -A POSTROUTING -s 192.168.251.2 -j MASQUERADE
      echo 1 > /proc/sys/net/ipv4/ip_forward

### Other ARAnyM host operating systems:
Instructions for setting up networking on Mac OS X and MS Windows ARAnyM hosts can be found/edited at http://wiki.aranym.org/

### FreeMiNT DNS setup:
AFROS needs to know the correct IP address of your DNS server. In most Linux/Unix operating systems this can be achieved by the following command:

    grep nameserver /etc/resolv.conf > drive_c/etc/resolv.conf

##News in this release
2008/12/17 = AFROS 8.12 (Ubuntu-like versioning)
* config: 64 MB FastRAM, [ETH0] reconfigured to 192.168.251.1<->2
* new EmuTOS 0.8.4+ (fresh CVS build)
* new FreeMiNT + XaAES (fresh CVS build)
* new Teradesk 3.97
* new Taskbar 4.10beta
* new HighWire 0.3.3beta9+ (fresh CVS build)
* fixed NFJPEG driver that can be started even after MiNT
* fixed HostFS.DOS driver that shows correct file timestamps
* newly added software for better Atari GEM desktop experience:
 + zView - image viewer with NatFeat support for fast image decoding
+ Aniplayer - multimedia player
+ Kronos 1.91 - CPU/memory/video/disk benchmark
+ aMail - POP3/SMTP mailer
+ aFTP - FTP client with preconfigured Atari FTP sites
+ aVNC - VNC client
+ aCalc - simple calculator with clipboard support
+ JayGroups II - an addition to Taskbar - the Start menu editor
+ OLGA - Object Linking enabled for aMail's external editor
+ BubbleGEM - bubble help for GEM applications
+ GlueSTiK - another TCP/IP stack for broader compatibility
+ ST-Zip, LZHShell - necessary tools for unpacking Atari archives

All the software is as preconfigured as possible. Lots of time went into testing and finetuning the package. Hope you'll enjoy it!

2008/02/02:
* new EmuTOS (fresh CVS build)
* new Teradesk 3.94

2007/07/23:
* new CVS build of fVDI and ARANYM.SYS driver
* new HighWire 0.3.3beta6
* 32 MB of FastRAM, gradients in XaAES

2007/07/22:
* 16 MB FastRAM, ungrab hotkey is Alt+Ctrl+Shift, [ETH0] configured
* new EmuTOS CVS build (with PUN INFO struct)
* TosWin2 2.7 for redirecting TOS/TTP program output to GEM window
* bin folder with bash, ifconfig and route for automatic network setup
* gemsys\ttf: DejaVu LGC Serif, Sans-Serif and monospaced TrueType fonts
* HighWire configured to use the nice antialiased fonts

2007/07/10:
* EmuTOS 0.8.2, fVDI 0.968beta4
* Teradesk 3.91, HighWire 0.3.2

## Contact:
For more information please visit http://aranym.org/afros

EnJoy!
Petr Stehlik
