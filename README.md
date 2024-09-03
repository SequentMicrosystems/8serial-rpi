# 8serial-rpi
Drivers for Sequent Microsystems [Eight Serial Ports HAT for Raspberry Pi](https://sequentmicrosystems.com/products/eight-raspberry-pi-serial-ports)

## Setup

Enable I2C communication first:
```bash
sudo raspi-config
```
A good article about I2C on Raspberry can be found [here](https://www.raspberrypi-spy.co.uk/2014/11/enabling-the-i2c-interface-on-the-raspberry-pi/).

If you use Ubuntu you need to install `raspi-config` first:
```bash
sudo apt update
sudo apt install raspi-config
```

Make sure you have all the tools you need:
```bash
sudo apt update
sudo apt-get install git build-essential
```


## Usage

### Kernel visible Serial ports and CAN

The card emulates 3 x SC16IS752 chips, each with two UART ports, and contains one MCP2515 CAN chip.

Setup:
Edit the ```/boot/config.txt``` or ```/boot/firmware/config.txt``` for the new Raspbians, adding the following lines depending on the card ID
 - ID = 0:
  ```bash
  #UART ports enable
  dtoverlay=sc16is752-i2c,int_pin=22,addr=0x6A,xtal=1843200
  dtoverlay=sc16is752-i2c,int_pin=19,addr=0x6C,xtal=1843200
  dtoverlay=sc16is752-i2c,int_pin=20,addr=0x6E,xtal=1843200
  #CAN port 
  dtparam=spi=on
  dtoverlay=mcp2515-can0,oscillator=16000000,interrupt=6
  dtoverlay=spi-bcm2835
  dtoverlay=spi-dma
  ```
 - ID = 1:
  ```bash
  #UART ports enable
  dtoverlay=sc16is752-i2c,int_pin=22,addr=0x6B,xtal=1843200
  dtoverlay=sc16is752-i2c,int_pin=19,addr=0x6D,xtal=1843200
  dtoverlay=sc16is752-i2c,int_pin=20,addr=0x6F,xtal=1843200
  #CAN port 
  dtparam=spi=on
  dtoverlay=mcp2515-can1,oscillator=16000000,interrupt=16
  dtoverlay=spi-bcm2835
  dtoverlay=spi-dma
  ```
After a restart open a terminal and run the following command ``` ls /dev ``` and you should see the ttySCx serial ports listed.

To check the CAN port run the following command ``` dmesg | grep can0 ```

The serial names that can be used and the correspondence with the card ports are as follows:
- dev/ttySC0  => RS232 PORT2
- dev/ttySC1 => RS485
- dev/ttySC2 = RS232 PORT3
- dev/ttySC3 = RS232 PORT1
- dev/ttySC4 = M-BUS
- dev/ttySC5 = RS422

For a complete reference of the CAN usage please check out the [LinuxJedi](https://linuxjedi.co.uk/2021/12/01/making-a-can-bus-module-work-with-a-raspberry-pi/comment-page-1/)

### One wire bus and additional features

Install the command:
```bash
git clone https://github.com/SequentMicrosystems/8serial-rpi.git
cd 8serial-rpi/
sudo make install
```

Now you can access the watchdog, one wire bus, and button features of the [Eight Serial Ports HAT for Raspberry Pi](https://sequentmicrosystems.com/products/eight-raspberry-pi-serial-ports) through the command "8serial". Use -h option for help:
```bash
8serial -h
```

If you clone the repository any update can be made with the following commands:
```bash
cd 8serial-rpi/  
git pull
sudo make install
```
