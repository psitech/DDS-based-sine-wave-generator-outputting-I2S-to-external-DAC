# ESP32-C3, DDS-based sine-wave generator, outputting I2S data to external DAC

This repository contains working Arduino sketches for outputting sine data to an external DAC over I2S.

**ESP32C3_I2S-sine-DDS-1024.ino** has a large 1024-entry, 16bit wide lookup table and uses Direct Digital Synthesis to generate the data.

**ESP32C3_I2S-sine-DDS-1024-Taylor-series.ino** generates a 1024-entry, 32bit wide lookup table in memory using the Taylor Series approximation. It also uses Direct Digital Synthesis to generate the data, outputted as a 64bit left-right sample to the DAC.

Sample rates of 44.1Khz, 48kHz, 88.2kHz or 96kHz are possible. The DAC can handle these sample rates without any problem [and will oversample the data at 384kHz before generating an analog signal]. Distortion measured lower than -60dB.

Hardware used: [1] ESP32-C3 SuperMini board, [2] a PMC5102A DAC module.

![image](https://github.com/psitech/DDS-based-sine-wave-generator-outputting-I2S-to-external-DAC/assets/27091013/5bd1f017-f873-42d2-b429-33b1ca9e7845)
