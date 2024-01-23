# DDS-based-sine-wave-generator-outputting-I2S-to-external-DAC
ESP32-C3, DDS-based sine-wave generator, ouputting I2S data to external DAC
This repository contains a working Arduino sketch for outputting sine data to an external DAC using I2S.

ESP32C3_I2S-sine-DDS-1024.ino has a large 1024-entry lookup table and uses Direct Digital Synthesis to send out the data.

Sample rates of 44.1Khz, 48kHz, 88.2kHz or 96kHz are possible. The DAC can handle these samplerates without any problem [and will oversample the data at 384kHz before generating an analog signal]. Distortion measured lower than -60dB.

Hardware used: [1] ESP32-C3 SuperMini board, [2] a PMC5102A DAC module.

![image](https://github.com/psitech/DDS-based-sine-wave-generator-outputting-I2S-to-external-DAC/assets/27091013/5bd1f017-f873-42d2-b429-33b1ca9e7845)
