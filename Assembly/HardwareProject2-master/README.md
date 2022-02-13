# README #

This project is a StarterKit for Uzebox which utilised the ATmega644 8 Bit Chipset
http://www.microchip.com/wwwproducts/en/ATmega644


### What is this repository for? ###

* StarterKit for Uzebox

### How do I get set up? ###

#### Quick Method (Linux) ####

* Download install.sh
* bash install.sh

#### Slow Method ####
* Clone repository
* Download and install Atmel AVR Toolchain
	* Windows http://www.atmel.com/tools/atmelavrtoolchainforwindows.aspx
	* Linux http://www.atmel.com/tools/ATMELAVRTOOLCHAINFORLINUX.aspx
* Install GNU Make https://www.gnu.org/software/make/
* Install AVR Dude `Tools/avrdude-win-64bit.zip`
* Clone Kernel https://github.com/Uzebox/uzebox.git

### Cloning Repository ###
* Run GitBash and type the Follow commands into GitBash

* Check Present Working Directory `pwd`

* Change to the C drive or other drive `cd c:`

* Make a projects Directory `mkdir projects`

* Change to the projects directory by `cd projects`

* Clone the project `git clone https://MuddyGames@bitbucket.org/MuddyGames/uzeboxstarterkit.git`

* Change to the project directory `cd projects uzeboxstarterkit`

* List files that were downloaded `ls`

### Installation and Environment Notes ###

On Windows ensure paths set for each of the following:

* `C:\Program Files\avr8-gnu-toolchain\bin`
* `C:\Program Files (x86)\GnuWin32\bin`
* `C:\Program Files\avrdude`

### Microcontroller Programmer ###

* Flashing ROM http://uzebox.org/wiki/index.php?title=Avrdude
* USBTiny Driver;
	* https://learn.adafruit.com/usbtinyisp
	* https://learn.adafruit.com/usbtinyisp/drivers


### Setting Up Eclipse (Editor) ###

* http://uzebox.org/wiki/index.php?title=Uzebox_Developement_Under_Eclipse
* GDB Options http://stackoverflow.com/questions/3758794/how-do-i-use-gdb-in-eclipse-for-c-c-debugging

### Useful Links ###

* http://fab.cba.mit.edu/classes/4.140/doc/projects/ftsmin/windows_avr.html
* USB Drivers http://zadig.akeo.ie/
* https://github.com/Uzebox/uzebox
* http://tilestudio.sourceforge.net/
* Setting up AVR Toolchain on MAC and Linux http://maxembedded.com/2015/06/setting-up-avr-gcc-toolchain-on-linux-and-mac-os-x/
* Window 8 http://www.avrfreaks.net/forum/windows-81-compilation-error?page=all
* Getting Started https://www.youtube.com/watch?v=vT2TUSZWDf8
* Lightweight Linux Distributions https://www.linux.com/news/best-lightweight-linux-distros-2017
* Boot USB Creator https://www.pendrivelinux.com/universal-usb-installer-easy-as-1-2-3/
* Booting a Live USB using VirtualBox https://www.howtogeek.com/187721/how-to-boot-from-a-usb-drive-in-virtualbox/
* AVR Assembly Code Beginner http://www.avr-asm-download.de/beginner_en.pdf
* KALI for https://www.kali.org
* Visual Studio Code https://code.visualstudio.com/docs/setup/linux
* Visual Studio Code Command line options https://code.visualstudio.com/docs/editor/command-line
* To find avr include path type `avr-gcc -print-file-name=include` into terminal
* Setup make integration with Visual Studio Code https://stackoverflow.com/questions/30269449/how-do-i-set-up-vscode-to-compile-c-code
* Beginners Introduction to the Assembly Language of ATMEL AVR Microprocessors http://www.avr-asm-download.de/beginner_en.pdf
* Linux Setup guide (used to create install.sh) http://www.ladyada.net/learn/avr/setup-unix.html
### Who do I talk to? ###
