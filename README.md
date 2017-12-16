# LambdaControl - MIOS32 Firmware

<img src="https://www.lambdaton.de/images/github/lambdacontrol.jpg" alt="Picture of LambdaControl" width="420">

This repository contains the MIOS32 firmware for my DIY MIDI controller project [LambdaControl](https://www.lambdaton.de/diy-hardware/lambda-control/). 

I designed and build LambdaControl for my upcoming live performance and decided to release all components under open source licenses, such that other artists can use my project as they like.

A complete documentation of the project can be found on my [website](https://www.lambdaton.de/diy-hardware/lambda-control/).

## Project Parts
LambdaControl is based on the [MIDIbox project](http://www.ucapps.de/), which provides a complete solution for basic tasks like reading analog and digital inputs (faders, knobs and encoders). However, the RGB button matrix of LambdaControl, which works like the matrix of a Novation Launchpad, required a complete custom development.

LambdaControl consists of the following parts: components from the MIDIbox project for the basic I/O and USB MIDI connection (this repository), separate microcontroller which controls the RGB matrix, and a MIDI Remote Script that connects the controller with Ableton Live over USB. Additionally, I created a repository for the hardware parts like the RGB button matrix PCB or the 3D printable case.

## MIOS32 Firmware
The [MIDIbox project](http://www.ucapps.de/) started by Thorsten Klose provides the foundation on which I have designed my controller. The project provides reliable hardware and a corresponding operating system [MIOS](http://www.ucapps.de/mios32_download.html).

This repository contains the firmware for the MIDIbox core and is written for the MIOS32 operating system (based on FreeRTOS). Actually, I used the [STM32F4 based Core](http://www.ucapps.de/mbhp_core_stm32f4.html), but the code should also work fine on the other core modules.

The firmware uses the [AINSER64 extension board](http://www.ucapps.de/mbhp_ainser64.html) to read the positions of the linear and rotary potentiometers. And the encoders with their additional button function are connected by a [DINx4 extension module](http://www.ucapps.de/mbhp_din.html).

Moreover, the MIOS core communicates with the RGB button matrix microcontroller unit (MCU) over I2C. Button presses are detected by the separate MCU and the MIOS core frequently pulls for these button changes. Additionally, changes to the button colors are forwarded by the MIOS core to the RGB button matrix MCU.

## License
LambdaControl's firmware is licensed under the MIT license, such that other artists can really make use of it. However, **the MIDIbox project is licensed for personal use only** and explicitly forbids the commercial use.

## Deploy
If you just want to upload the code to your STM32F4 based MIDIbox core, you can make use of the pre build firmware found inside the release folder of the repository. Simply, upload the firmware to the core by using [MIOS Studio](http://www.ucapps.de/mios_studio.html).

## Compile
The project can be build with the ARM-based toolchain provided by the MIDIbox project. Therefore, follow their tutorial to install it. If you're on a Linux system, you can find the tutorial [here](http://www.midibox.org/dokuwiki/doku.php?id=linux_mios32_toolchain_core).

On my Debian 9 based dev system the following problems arised during this installation:

 * use tar inside the tutorial with the flags **jxvf** s.t it can uncompress the bzip2 file
 * install the following additional packages to get the toolchain working:

```bash
sudo apt-get install lib32z1 lib32ncurses5
```

Finally, adjust the following MIOS32 environment variables to build for the STM32F4-DISCOVERY based core, before starting the build with make.
 
```bash
export MIOS32_FAMILY="STM32F4xx"
export MIOS32_PROCESSOR="STM32F407VG"
export MIOS32_BOARD="MBHP_CORE_STM32F4"
export MIOS32_LCD="universal"
```

After that deploy the firmware to the core by using [MIOS Studio](http://www.ucapps.de/mios_studio.html).

## Author

2017 - LambdaTon 
  
