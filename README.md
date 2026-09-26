# Ryujin III Control Software

> [!WARNING]
> This is an unofficial development to manage Asus Ryujin III water cooling under linux systems.
> Use it under your own responsibility. This is still a work in progress.

> [!NOTE]
> Feel free to file any bug you found.

> [!IMPORTANT]
> UDEV RULES ONLY REQUIRED FOR DEVELOPMENT.<br>
> Currently DEB package has a post install script which creates an udev rule and retriggers udev rules.<br>

> [!NOTE]
> Creating UDEV rules
> <br> 1. Find your usb device, by executing lsusb.
> <br> 2. Copy the values separated by ":", the one on the left is the idVendor, while the one on the right is the
idProduct.
> <br> 3. Create an udev rule, (use sudo) by creating a file inside the following directory /etc/udev/rules.d/[name]
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
> 6. Execute binary without sudo, it should work now, if not sometimes it will require you to restart the machine.

<br><br>
Software to help you control your Asus Ryujin III Water Cooling under linux. Right now I only support Debian 13 (And
probably some Debian base distros). This work was done through reverse engineering Ryujin III usb packets under linux
using wireshark (usbmon) to capture. Also, using libusb 1.0.0 to communicate with Ryujin interface.

If you find this useful, please consider making a donation. Thanks!<br><br>
[<img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png"  height="50">](https://www.buymeacoffee.com/iscluis06)

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
- [x] Remove gif from memory.
- [x] Turn off the display.
- [x] Turn on the display.
- [x] Fan control
- [x] Display hardware monitor (It may require a daemon to report sensor data).
- [x] Upload jpeg images to LED display.
- [ ] Feature to keep track of uploaded images. (I still need to validate if possible, not found any descriptor
  reporting available slots)
- [ ] Slideshow effect for images.
- [x] Clock effect.

Special thanks to https://github.com/liquidctl/liquidctl
and https://github.com/BrandonKynoch/asus-rog-ryujin-iii-linux-controller @BrandonKynoch, without your findings this may
not be possible.

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
Ryujin III Management Tool
    Current hardware monitor implementations:
    0 - Ryujin Liquid Temp
    1 - Ryujin Fan Speed
    2 - Ryujin Pump Speed
    3 - Amd Core Temp
    4 - Git Last Commiter [param: path to git local repo]

  OPTIONS:

      -h, --help                        Display help menu
      --lon                             Turn on the led display
      --fan-speed-config=[fan speed
      config]                           Fan Speed config
      --pump-speed-config=[pump speed
      config]                           Pump Speed config
      --loff                            Turn off the led display
      --default-gif                     Displays the default gif
      --hw-monitor                      Displays default hardware monitor, 1
                                        line, mode cyberpunk, style 1 and ryujin
                                        liquid temp implement.
                                        Cancel loop by using ctrl+c
      --hw-monitor-config               Configures a hardware monitor specify
                                        lines by using line parameters for
                                        example --line1, --mode for mode
                                        [galactic = 0, cyberpunk = 1], --style
                                        from 0 up to 3.
                                        Example: --hw-monitor-config --line1=0
                                        --mode=1 --style=0
                                        Cancel loop by using ctrl+c
      --line1=[line1]                   Configures the first line for hardware
                                        monitor, refer to hardware monitor
                                        implementations for options
      --line2=[line2]                   Configures the first line for hardware
                                        monitor, refer to hardware monitor
                                        implementations for options
      --line3=[line3]                   Configures the first line for hardware
                                        monitor, refer to hardware monitor
                                        implementations for options
      --git-repo-path=[git repo path]   Specifies the path to the git repo for
                                        Git Last Commiter implementation
      --mode=[mode]                     Specifies the mode for hardware monitor,
                                        currently only galactic=0 and
                                        cyberpunk=1 available
      --style=[style]                   Specifies the style for hardware
                                        monitor, from 0 up to 3 available
      --select-gif=[select gif]         Select a gif from memory
      --select-jpeg=[select jpeg]       Select a jpeg from memory
      --delete-from-memory=[delete from
      memory]                           Delete a gif from memory
      --upload-gif=[upload gif]         Upload gif, it should be set along side
                                        select option, you must specify a memory
                                        slot to upload to
      --upload-jpeg=[upload jpeg]       Upload jpeg, it should be set along side
                                        select option, you must specify a memory
                                        slot to upload to
      --clock-mode                      Activates clock mode
```

Example turning off the led display

```shell
./ryujinIII --loff
```

Example uploading a gif

```shell
# Select a different memory slot that the one you want to upload to
./ryujinIII --select-gif 2
# Upload the gif to the selected memory slot, it sometimes will fail on the first try
./ryujinIII --upload-gif some_path/to_some_gif/image.gif --select-gif 1
```

Example uploading a jpeg

```shell
# Select a different memory slot that the one you want to upload to
./ryujinIII --select-jpeg 4
# Upload the gif to the selected memory slot, it sometimes will fail on the first try
./ryujinIII --upload-jpeg some_path/to_some_jpeg/image.jpeg --select-jpeg 4
```

Example of hardware monitor config with liquid temp implementation

```shell
./ryujinIII --hw-monitor-config --style 0 --mode 1 --line1 0
```

Example of hardware monitor config with liquid temp implementation, fan speed

```shell
./ryujinIII --hw-monitor-config --style 0 --mode 1 --line1 0 --line2 1
```

Example of hardware monitor config with liquid temp implementation, fan speed and amd core temp

```shell
./ryujinIII --hw-monitor-config --style 0 --mode 1 --line1 0 --line2 1 --line3 3
```

Example of hardware monitor config with git repo.

```shell
./ryujinIII --hw-monitor-config --style 0 --mode 1 --line1 4 --git-repo="path to repo"
```

To close all hardware loops just press ctrl+C.<br><br>
Example of fan speed configuration, refer to the below tables for RPM's.

```shell
./ryujinIII --fan-speed-config 50
```

Example of pump speed configuration, refer to the below tables for RPM's.

```shell
./ryujinIII --pump-speed-config 50
```

Example of clock mode

```shell
./ryujinIII --clock-mode
```

Currently I use a best effort formula to guess and configure the speeds, whenever you
set a speed for PUMP or FANS, command will try to update both devices, it is not perfect.

## Speed config for pump and fans

Current speed configs taken directly from device reporting:

### Fan speeds

Even so when sensors don't report back from 26 and below, by observing the
fans, those are set by default to a lower rpm, which is not being reported back.

| Hex value | Decimal Value | RPM's | Hex value | Decimal Value | RPM's |
|-----------|---------------|-------|-----------|---------------|-------|
| 0x1       | 1             | 0     | 0x33      | 51            | 	2310  |
| 0x2       | 2             | 0     | 0x34      | 52            | 	2370  |
| 0x3       | 3             | 0     | 0x35      | 53            | 	2460  |
| 0x4       | 4             | 0     | 0x36      | 54            | 	2520  |
| 0x5       | 5             | 0     | 0x37      | 55            | 	2580  |
| 0x6       | 6             | 0     | 0x38      | 56            | 	2640  |
| 0x7       | 7             | 0     | 0x39      | 57            | 	2700  |
| 0x8       | 8             | 0     | 0x3A      | 58            | 	2760  |
| 0x9       | 9             | 0     | 0x3B      | 59            | 	2820  |
| 0xA       | 10            | 0     | 0x3C      | 60            | 	2880  |
| 0xB       | 11            | 0     | 0x3D      | 61            | 	2940  |
| 0xC       | 12            | 0     | 0x3E      | 62            | 	3000  |
| 0xD       | 13            | 0     | 0x3F      | 63            | 	3060  |
| 0xE       | 14            | 0     | 0x40      | 64            | 	3090  |
| 0xF       | 15            | 0     | 0x41      | 65            | 	3180  |
| 0x10      | 16            | 0     | 0x42      | 66            | 	3270  |
| 0x11      | 17            | 0     | 0x43      | 67            | 	3360  |
| 0x12      | 18            | 0     | 0x44      | 68            | 	3420  |
| 0x13      | 19            | 0     | 0x45      | 69            | 	3540  |
| 0x14      | 20            | 0     | 0x46      | 70            | 	3570  |
| 0x15      | 21            | 0     | 0x47      | 71            | 	3660  |
| 0x16      | 22            | 0     | 0x48      | 72            | 	3690  |
| 0x17      | 23            | 0     | 0x49      | 73            | 	3780  |
| 0x18      | 24            | 0     | 0x4A      | 74            | 	3780  |
| 0x19      | 25            | 0     | 0x4B      | 75            | 	3900  |
| 0x1A      | 26            | 0     | 0x4C      | 76            | 	3930  |
| 0x1B      | 27            | 660   | 0x4D      | 77            | 	4020  |
| 0x1C      | 28            | 690   | 0x4E      | 78            | 	4050  |
| 0x1D      | 29            | 810   | 0x4F      | 79            | 	4140  |
| 0x1E      | 30            | 840   | 0x50      | 80            | 	4200  |
| 0x1F      | 31            | 930   | 0x51      | 81            | 	4230  |
| 0x20      | 32            | 990   | 0x52      | 82            | 	4290  |
| 0x21      | 33            | 1050  | 0x53      | 83            | 	4350  |
| 0x22      | 34            | 1140  | 0x54      | 84            | 	4410  |
| 0x23      | 35            | 1230  | 0x55      | 85            | 	4470  |
| 0x24      | 36            | 1260  | 0x56      | 86            | 	4560  |
| 0x25      | 37            | 1350  | 0x57      | 87            | 	4620  |
| 0x26      | 38            | 1410  | 0x58      | 88            | 	4620  |
| 0x27      | 39            | 1500  | 0x59      | 89            | 	4710  |
| 0x28      | 40            | 1530  | 0x5A      | 90            | 	4710  |
| 0x29      | 41            | 1620  | 0x5B      | 91            | 	4830  |
| 0x2A      | 42            | 1680  | 0x5C      | 92            | 	4890  |
| 0x2B      | 43            | 1770  | 0x5D      | 93            | 	4950  |
| 0x2C      | 44            | 1800  | 0x5E      | 94            | 	4980  |
| 0x2D      | 45            | 1890  | 0x5F      | 95            | 	5100  |
| 0x2E      | 46            | 1920  | 0x60      | 96            | 	5190  |
| 0x2F      | 47            | 2010  | 0x61      | 97            | 	5370  |
| 0x30      | 48            | 2070  | 0x62      | 98            | 	5340  |
| 0x31      | 49            | 2190  | 0x63      | 99            | 	5400  |
| 0x32      | 50            | 2220  | 0x64      | 100           | 	5370  |

### Pump speeds

| Hex value | Decimal Value | RPM's | Hex value | Decimal Value | RPM's |
|-----------|---------------|-------|-----------|---------------|-------|
| 0x01      | 1             | 870   | 0x033     | 51            | 	2160  |
| 0x02      | 2             | 870   | 0x034     | 52            | 	2190  |
| 0x03      | 3             | 870   | 0x035     | 53            | 	2250  |
| 0x04      | 4             | 870   | 0x036     | 54            | 	2280  |
| 0x05      | 5             | 870   | 0x037     | 55            | 	2340  |
| 0x06      | 6             | 870   | 0x038     | 56            | 	2370  |
| 0x07      | 7             | 870   | 0x039     | 57            | 	2400  |
| 0x08      | 8             | 870   | 0x03A     | 58            | 	2430  |
| 0x09      | 9             | 870   | 0x03B     | 59            | 	2460  |
| 0x0A      | 10            | 840   | 0x03C     | 60            | 	2460  |
| 0x0B      | 11            | 840   | 0x03D     | 61            | 	2520  |
| 0x0C      | 12            | 870   | 0x03E     | 62            | 	2550  |
| 0x0D      | 13            | 840   | 0x03F     | 63            | 	2610  |
| 0x0E      | 14            | 840   | 0x040     | 64            | 	2610  |
| 0x0F      | 15            | 870   | 0x041     | 65            | 	2640  |
| 0x010     | 16            | 870   | 0x042     | 66            | 	2670  |
| 0x011     | 17            | 870   | 0x043     | 67            | 	2730  |
| 0x012     | 18            | 870   | 0x044     | 68            | 	2730  |
| 0x013     | 19            | 870   | 0x045     | 69            | 	2790  |
| 0x014     | 20            | 870   | 0x046     | 70            | 	2790  |
| 0x015     | 21            | 870   | 0x047     | 71            | 	2850  |
| 0x016     | 22            | 870   | 0x048     | 72            | 	2850  |
| 0x017     | 23            | 900   | 0x049     | 73            | 	2910  |
| 0x018     | 24            | 990   | 0x04A     | 74            | 	2910  |
| 0x019     | 25            | 1050  | 0x04B     | 75            | 	2970  |
| 0x01A     | 26            | 1110  | 0x04C     | 76            | 	2970  |
| 0x01B     | 27            | 1170  | 0x04D     | 77            | 	3000  |
| 0x01C     | 28            | 1200  | 0x04E     | 78            | 	3030  |
| 0x01D     | 29            | 1230  | 0x04F     | 79            | 	3090  |
| 0x01E     | 30            | 1320  | 0x050     | 80            | 	3090  |
| 0x01F     | 31            | 1380  | 0x051     | 81            | 	3120  |
| 0x020     | 32            | 1410  | 0x052     | 82            | 	3120  |
| 0x021     | 33            | 1440  | 0x053     | 83            | 	3180  |
| 0x022     | 34            | 1500  | 0x054     | 84            | 	3210  |
| 0x023     | 35            | 1530  | 0x055     | 85            | 	3240  |
| 0x024     | 36            | 1590  | 0x056     | 86            | 	3240  |
| 0x025     | 37            | 1650  | 0x057     | 87            | 	3270  |
| 0x026     | 38            | 1650  | 0x058     | 88            | 	3270  |
| 0x027     | 39            | 1710  | 0x059     | 89            | 	3330  |
| 0x028     | 40            | 1740  | 0x05A     | 90            | 	3360  |
| 0x029     | 41            | 1800  | 0x05B     | 91            | 	3390  |
| 0x02A     | 42            | 1830  | 0x05C     | 92            | 	3390  |
| 0x02B     | 43            | 1860  | 0x05D     | 93            | 	3420  |
| 0x02C     | 44            | 1920  | 0x05E     | 94            | 	3450  |
| 0x02D     | 45            | 1920  | 0x05F     | 95            | 	3480  |
| 0x02E     | 46            | 1980  | 0x060     | 96            | 	3480  |
| 0x02F     | 47            | 2010  | 0x061     | 97            | 	3510  |
| 0x030     | 48            | 2040  | 0x062     | 98            | 	3540  |
| 0x031     | 49            | 2100  | 0x063     | 99            | 	3540  |
| 0x032     | 50            | 2130  | 0x064     | 100           | 	3630  |
