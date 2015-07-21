# mcp3424

Linux userspace I2C module for the MCP3424 ADC. Code was originally ported from the code found [here](https://github.com/abelectronicsuk/ABElectronics_Python3_Libraries/tree/master/ADCPi). This has been used with ABElectronics' ADC Pi and ADC Pi Plus. See [main.c](main.c) for an example of how to use the module.

To compile main.c run:

```bash
make
```

to test run:

```bash
./main
```

Ensure that the device is correct for your adapter e.g. on Raspberry Pi Model A+ and Raspberry Pi 2 Model B the device is `/dev/i2c-1`.
