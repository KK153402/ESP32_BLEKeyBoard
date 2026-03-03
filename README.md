# ESP32-C3 BLE Keyboard

A compact wireless keyboard with 2 programmable keys, built around the ESP32-C3 microcontroller. Communicates via Bluetooth Low Energy (BLE) and is powered by a Li-ion battery with USB-C charging.

> PCBWay Project Page: [ESP32-C3 BLE Keyboard - Battery Powered with USB-C Charging](https://www.pcbway.com/project/shareproject/ESP32_C3_BLE_Keyboard_Battery_Powered_with_USB_C_Charging_1821926f.html)

![完成品](docs/images/Realshot.png)

---

## Features

- **2-key BLE HID Keyboard** — works with PC, Mac, Android, and iOS
- **Battery powered** — single-cell Li-ion (3.7V)
- **USB Type-C charging** — with TP4056 + protection circuit
- **Auto-programming** — no need to manually press BOOT/EN buttons (FT231XS + auto-reset circuit)
- **Compact design** — easy to carry and use at a workstation

---

## Hardware

| Component | Description |
|---|---|
| MCU | ESP32-C3 |
| USB-UART | FT231XS |
| Charging IC | TP4056 (with protection) |
| Battery | Li-ion single cell (3.7V) |
| Connector | USB Type-C |
| Buttons | BOOT, EN (physical), + 2x user keys |

---

## Firmware

- Developed with **PlatformIO**
- Uses the [ESP32-BLE-Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard) library
- Implements standard BLE HID keyboard profile
- 50ms debounce protection on key inputs

---

## Design Files

| File | Tool |
|---|---|
| Schematic | KiCad 9.0 |
| PCB Layout | KiCad 9.0 |
| Enclosure (3D) | Autodesk Fusion 360 |
| Gerber / BOM / Centroid | — |

---

## Repository Structure

```
ESP32_BLEKeyBoard/
├── firmware/        # PlatformIO project (src/, platformio.ini)
├── hardware/        # KiCad schematic & PCB files
├── enclosure/       # Fusion 360 / STEP files
├── docs/            # Schematic PDF, BOM, etc.
└── README.md
```

---

## Getting Started

### Requirements

- [PlatformIO](https://platformio.org/) (VS Code extension recommended)
- ESP32-BLE-Keyboard library (installed via `platformio.ini`)

### Build & Flash

```bash
# Clone the repository
git clone https://github.com/KK153402/ESP32_BLEKeyBoard.git
cd ESP32_BLEKeyBoard

# Open in VS Code with PlatformIO, then:
# Build:  Ctrl+Alt+B
# Upload: Ctrl+Alt+U
```

Auto-programming is supported via the FT231XS + DTR/RTS reset circuit — no manual button presses needed.
