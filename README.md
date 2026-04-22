# Ryujin III Control Software

> [!WARNING]
> This is an unofficial development to manage Asus Ryujin III water cooling under linux systems.
> Use it under your own responsibility. This is still a work in progress.

> [!NOTE]
> Feel free to file any bug you found.


Software to help you control your Asus Ryujin III Water Cooling under linux.
Right now I only support Debian 13 (And probably some Debian base distros).
This work was done through reverse engineering Ryujin III usb packets under linux using wireshark (usbmon) to capture.
Also, using libusb 1.0.0 to communicate with Ryujin interface.

### Requirements
*  Debian 13 (It may also work on some debian based distros)
*  libusb 1.0 (shared library)
*  libudev (shared library)
*  libargs-dev (header only library, only required for development)

Use the following to install the required dependencies.

```shell
apt install libusb-1.0-0 libusb-1.0-0-dev
# Optional if you want to write some code or test the project
apt install libargs-dev
```

### Roadmap
- [x] Upload gifs to the LED display.
- [x] Select gif to display on.
- [x] Remove gif from memory.
- [x] Turn off the display.
- [x] Turn on the display.
- [] Fan control
- [] Display hardware monitor (It may require a daemon to report sensor data).
- [] Upload jpeg images to LED display.
- [] Feature to keep track of uploaded images. (I still need to validate if possible, not found any descriptor reporting available slots)
- [] Slideshow effect for images.
- [] Clock effect.


### Know issues, limitations and bugs

* I haven't found a reliable way to identify which memory slots are already occupied, so be cautious when uploading gifs,
because those may overwrite previous resources and may trigger a device reset.
* Selecting an empty slot may trigger a reset on the device.
* Uploading of images (gifs/jpegs) sometimes fails on the first try, and it requires a second run to make it work (I'm still trying to diagnose the issue.)
* Cropping and transformation of gif images will be done automatically; right now I have not implemented any functionality to allow the user to specify those parameters.
* Uploading of images must select a memory slot.