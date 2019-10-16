SimpleKalmanFilter pressureKalmanFilter(0.1, 0.02, 0.01);
U8G2_SSD1306_64X48_ER_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
TinyGPSPlus gps;
MAX30105 heartratesensor;
BMP180 bmp180;
