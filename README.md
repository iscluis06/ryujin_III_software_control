# Ryujin III Control Software

> [!WARNING]
> This is an unofficial development to manage Asus Ryujin III water cooling under linux systems.
> Use it under your own responsibility. This is still a work in progress.

> [!NOTE]
> Feel free to file any bug you found.

> [!IMPORTANT]
> You require sudo or root privelegies in order to execute the binary, you can also set up udev
> rules to allow any user to access ryujin usb interface.

> [!NOTE]
> Creating UDEV rules
> <br> 1. Find your usb device, by executing lsusb.
> <br> 2. Copy the values separated by ":", the one on the left is the idVendor, while the one on the right is the
idProduct.
> <br> 3. Create a udev rule, (use sudo) by creating a file inside the following directory /etc/udev/rules.d/[name]
.rules, you can
name it as you like being the only requirement to have ".rules" at the end.
> <br> 4. Copy/Paste the following by replacing IDVENDOR and IDPRODUCT by the values from step 2:
> ```shell
> SUBSYSTEM=="usb", ATTRS{idVendor}=="IDVENDOR", ATTRS{idProduct}=="IDPRODUCT", TAG+="uaccess", MODE="0666"
> ```
> Save it and close it
> <br> 5. Execute the following command to reload udev rules:
> ```shell
> sudo udevadm control --reload-rules
> sudo udevadm trigger
> ```
> 6. Execute binary without sude, it should work now, if not sometimes it will require you to restart the machine.

<br><br>
Software to help you control your Asus Ryujin III Water Cooling under linux. Right now I only support Debian 13 (And
probably some Debian base distros). This work was done through reverse engineering Ryujin III usb packets under linux
using wireshark (usbmon) to capture. Also, using libusb 1.0.0 to communicate with Ryujin interface.

### Requirements

* Debian 13 (It may also work on some debian based distros)
* libusb 1.0 (shared library)
* libudev (shared library)
* libargs-dev (header only library, only required for development)
* imagemagick (needed to prepare gifs)

Use the following to install the required dependencies.

```shell
apt install libusb-1.0-0 libusb-1.0-0-dev libmagick++-7-headers imagemagick
# Optional if you want to write some code or test the project
apt install libargs-dev
```

### Roadmap

- [x] Upload gifs to the LED display.
- [x] Select gif to display on.
- [ ] Remove gif from memory.
- [x] Turn off the display.
- [x] Turn on the display.
- [ ] Fan control
- [ ] Display hardware monitor (It may require a daemon to report sensor data).
- [ ] Upload jpeg images to LED display.
- [ ] Feature to keep track of uploaded images. (I still need to validate if possible, not found any descriptor
  reporting available slots)
- [ ] Slideshow effect for images.
- [ ] Clock effect.

### Know issues, limitations and bugs

* I haven't found a reliable way to identify which memory slots are already occupied, so be cautious when uploading
  gifs, because those may overwrite previous resources and may trigger a device reset.
* Selecting an empty slot may trigger a reset on the device.
* Uploading of images (gifs) sometimes fails on the first try, and it requires a second run to make it work (I'm still
  trying to diagnose the issue.)
* I'm currently using image magick command line to transform gifs images to a compatible format for ryujin display:
    * Colors 64
    * Color palette web/netscape
    * 320x240 widthxheight
    * Dispose method 1
    * Background black
* I couldn't find a reliable way to recreate a valid gif programatically using libvips or by gifsicle command.
* Right now the only way to make a gif file to display is to force its size to a multiple of 4096 bytes.<br>When
  uploading on windows this requirement is not needed (Posible bug).

### Usage

```shell
Ryujin III Managment Tool

  OPTIONS:

      -h, --help                        Display help menu
      --lon                             Turn on the led display
      --loff                            Turn off the led display
      --select-gif=[select_gif]         Select a gif from memory
      --delete=[delete]                 Delete a gif from memory
      --upload-gif=[upload_gif]         Upload gif, it should be set along side
                                        select option, you must specify a memory
                                        slot to upload to
```

Example turning off the led display

```shell
./ryujinIII --loff
```

Example turning uploading a gif

```shell
# Select a different memory slot that the one you want to upload to
./ryujinIII --select-gif 2
# Upload the gif to the selected memory slot, it sometimes will fail on the first try
./ryujinIII --upload-gif some_path/to_some_gif/image.gif --select-gif 1
```