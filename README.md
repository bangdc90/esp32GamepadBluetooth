Hướng dẫn:
Linh kiện cần:
1 esp32
- TX-RX có ibus (ví dụ Flysky i6, IA6B)
2. Kết nối dây:
- GND của RX nối GND của ESP32
- Vcc của RX nối 3.3V của ESB32
- Chân tx ibus của rx nối vơi chân RX2 trên ESP32
- Hàn pin 1s vào chân GND-Vin trên esp32.
3. Firmware build sẵn:
- Download tại: https://drive.google.com/.../1FxV0NaL8gBOfnZdy7Zy.../view...
- Sử dụng flash_download_tool để nạp vào esp32, thiết lập như ảnh trong file tải bên trên (Khi bấm Start trên phần mềm để nạp, bấm nút Boot trên ESP32 vài lần để nhận chế độ flash, sau khi flash sẽ hiện FINISH)
4. Kết nối với PC hoặc điện thoại Android qua bluetooth, sau đó vào các phần mềm Simulator để calibrate các kênh với phần mềm)

Để build mã nguồn, cần cài thêm các thư viện:
- https://github.com/lemmingDev/ESP32-BLE-Gamepad
- https://github.com/h2zero/NimBLE-Arduino
- FlySkyIbus by Tim Wilkinson (https://gitlab.com/timwilkinson/FlySkyIBus)

Credits :
Credits to wakwak-koba for the NimBLE code that he provided.
Credits to Tim Wilkinson for FlySkyIbus 