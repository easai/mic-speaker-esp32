#include <Arduino.h>
#include <driver/i2s.h>

#define SAMPLE_RATE     16000
#define BUFFER_SIZE     512

#define I2S_BCLK        2     // Shared BCLK
#define I2S_LRCLK       3     // Shared LRCLK
#define I2S_DIN         0     // MS3625 SD (input)
#define I2S_DOUT        4     // MAX98357A DIN (output)

void setupI2S() {
  i2s_config_t i2s_config = {
    .mode =  i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_RX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S_MSB,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = BUFFER_SIZE,
    .use_apll = false,
    .tx_desc_auto_clear = true,
    .fixed_mclk = 0
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_BCLK,
    .ws_io_num = I2S_LRCLK,
    .data_out_num = I2S_DOUT,
    .data_in_num = I2S_DIN
  };

  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);
}

void setup() {
  Serial.begin(115200);
  setupI2S();
  Serial.println("Loopback started");
}

void loop() {
  uint8_t buffer[BUFFER_SIZE];
  size_t bytesRead;

  // Read from mic
  i2s_read(I2S_NUM_0, buffer, BUFFER_SIZE, &bytesRead, portMAX_DELAY);

  // Write to speaker
  i2s_write(I2S_NUM_0, buffer, bytesRead, &bytesRead, portMAX_DELAY);
}
