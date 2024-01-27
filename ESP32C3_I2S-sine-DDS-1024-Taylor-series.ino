// https://www.pjrc.com/high-precision-sine-wave-synthesis-using-taylor-series/
// https://vanhunteradams.com/DDS/DDS.html

#include "driver/i2s.h"
#define LUTsize 1024

float frequency = 9973;    // desired output frequency e.g. 19937, 9973, 997
float samplerate = 48000;  // desired output sample rate e.g 44100, 48000, 88200 or 96000
uint32_t phaseAcc = 0;     // phase accumulator
uint32_t phaseInc = 0;     // phase increment, also known as 'tuning word'
uint64_t LRsample = 0;     // 64 bit (left + right) sample
size_t bytes_written;      // return value from i2s_write() function
int32_t LUT[LUTsize];      // define 32 bit wide LUT

void setup() {
  generateTaylorSeriesSineTable();

  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = (uint32_t)samplerate,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 2,
    .dma_buf_len = 512,
    .use_apll = true,
    .tx_desc_auto_clear = true,
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = 10,
    .ws_io_num = 20,
    .data_out_num = 21,
    .data_in_num = I2S_PIN_NO_CHANGE
  };

  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);

  phaseInc = (uint32_t)((frequency / samplerate) * pow(2, 32));
}

void loop() {
  LRsample = (((uint64_t)((uint32_t)LUT[(phaseAcc >> 22)])) << 32) | ((uint32_t)LUT[(phaseAcc >> 22)]);
  i2s_write(I2S_NUM_0, &LRsample, 8, &bytes_written, portMAX_DELAY);
  phaseAcc += phaseInc;
}

void generateTaylorSeriesSineTable() {
  for (int i = 0; i < LUTsize; ++i) {
    double x = i * TWO_PI / LUTsize;
    double sum = 0.0;

    for (int j = 0; j <= 11; ++j) {  // use 11 terms in the Taylor series
      double term = pow(-1, j) * pow(x, 2 * j + 1) / taylorSeriesFactorial(2 * j + 1);
      sum += term;
    }

    LUT[i] = round(sum * 2147483648);  // multiply by 2147483648 (2^31) for full-scale output
  }
}

double taylorSeriesFactorial(int n) {
  double fact = 1.0;
  for (int i = 1; i <= n; ++i) {
    fact *= i;
  }
  return fact;
}
