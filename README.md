# ShutAir - WiFi-Controlled Shutter System

A WiFi-controlled shutter management system using ESP32-WROOM-32E microcontroller and RF transmitter.

## Hardware Requirements

- **MCU**: ESP32-WROOM-32E
- **RF Transmitter**: Connected to GPIO 4
- **Additional**: WiFi connectivity, USB power supply

## Software Requirements

### Arduino Libraries

Install the following libraries in Arduino IDE:

- **ESP32 Board Support**: `espressif32` (via Board Manager)
- **ESPAsyncWebServer**: For async HTTP server
- **AsyncTCP**: Required by ESPAsyncWebServer
- **LittleFS**: Built-in with ESP32 core (file system)
- **RFControl**: For RF transmission
- **Wire**: I2C communication (built-in)

### Board Configuration

In Arduino IDE, select:
- **Board**: ESP32-WROOM-32E
- **Flash Size**: 4MB
- **Partition Scheme**: Default (4MB with SPIFFS)
- **Upload Speed**: 921600 (or appropriate for your USB adapter)

## Setup Instructions

### 1. Configure Local Settings

Copy the configuration template:

```bash
cp .config/config.example.h .config/config.h
```

Edit `.config/config.h` with your local values:

```cpp
const String AUTH_PIN = "YOUR_PIN_HERE";

const WiFiConfig WIFI_CONFIG = {
  .ssid = "YOUR_SSID_HERE",
  .password = "YOUR_PASSWORD_HERE"
};

const Controller CONTROLLER_CONFIG = {
  .transmitterPin = 4,        // GPIO 4
  .buckets = { 366, 736, 1600, 5204, 10896 },
  .id = 108289123
};

const int SERVER_PORT = 8181;
```

### 2. Configure Web Application

Copy the web application config template:

```bash
cp .config/application-config.example.json data/www/application-config.json
```

Edit `data/www/application-config.json` with your shutter channels and favorites.

### 3. Upload to ESP32

1. Connect ESP32-WROOM-32E via USB
2. Select the correct port in Arduino IDE
3. Verify the board settings (as listed above)
4. Compile and upload the sketch

### 4. Upload File System

1. Go to **Tools → ESP32 Sketch Data Upload**
2. This uploads all files in the `data/` folder to LittleFS

### 5. Access the Web Interface

1. Check the Serial Monitor (115200 baud) for the IP address
2. Open `http://<ESP32_IP>:8181` in your browser
3. Enter your PIN code to authenticate

## Features

- **Web-based UI**: Control shutters from any device on your network
- **Channel Control**: Support for up to 16 shutter channels
- **Favorites**: Group multiple channels for quick control
- **PIN Authentication**: Simple PIN-based access control
- **Responsive Design**: Works on desktop and mobile devices
- **RF Transmission**: Wireless control of shutter motors

## API Endpoints

- `GET /authenticate` - Verify PIN access (requires Authorization header)
- `GET /up?id=<channel>` - Open a shutter channel
- `GET /down?id=<channel>` - Close a shutter channel
- `GET /stop?id=<channel>` - Stop shutter movement
- `GET /application-config.json` - Get web app configuration

## File Structure

```
wifi-server/
├── .config/
│   ├── config.h                    (local config - gitignored)
│   ├── config.example.h            (template)
│   └── application-config.example.json
├── data/
│   └── www/
│       ├── index.html
│       ├── style.css
│       ├── application-config.json (local config - gitignored)
│       ├── scripts/
│       │   ├── command.js
│       │   ├── config.js
│       │   ├── grid-factory.js
│       │   └── network.js
│       └── icons/
├── wifi-server.ino
├── wifi-config.h
├── controller.h
├── auth-handler.h/cpp
├── command-handler.h/cpp
├── pulse-generator.h/cpp
└── .gitignore
```

## Troubleshooting

### Serial Monitor shows "Connecting to WiFi..."

- Verify SSID and password in `.config/config.h`
- Check WiFi router is broadcasting SSID
- Check signal strength in the area

### Web interface not loading

- Verify ESP32 IP address from Serial Monitor
- Check port 8181 is accessible
- Verify LittleFS upload was successful

### Shutter commands not working

- Verify RF transmitter is properly connected to GPIO 4
- Check controller ID and bucket timings are correct
- Verify RF receiver is within range

## License

This project is open source. See LICENSE file for details.
