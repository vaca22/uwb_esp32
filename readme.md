I find that issue is not related to ESP32-S3. Setting SPI_EDGE bit of DW1000 to 1 fixed that problem.

SPI_EDGE (reg:04:00 bit:10)
SPI data launch edge. This bit allows the system integrator the ability to control the
launch edge used for SPI data from the DW1000 on the MISO SPI data output line. This
may be used to select the MISO output operation most suitable to the target system.
When SPI_EDGE is 0 the DW1000 uses the sampling edge to launch MISO data. This
setting should give the highest rate operation. When SPI_EDGE is 1 the DW1000 uses the
opposite edges to launch the data. This setting may give a more robust operation.