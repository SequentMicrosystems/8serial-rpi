# Update

The [Eight Serial Ports 2-Layer Stackable HAT for Raspberry Pi](https://sequentmicrosystems.com/products/eight-raspberry-pi-serial-ports) contains two Cortex microcontrolles wich can be uptated with the last firmware version from the Sequent Microsystems servers.
To do that you need to browse to the "update" folder ```cd 8serial-rpi/update``` and update CPU 1:
```bash
./update 0 1
```
where the first parameter (0) is the stack level and update CPU 2:
```bash
./update 0 2
```

