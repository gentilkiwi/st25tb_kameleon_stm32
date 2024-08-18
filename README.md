# st25tb_kameleon_stm32

ST25TB / SRx NFC Emulator / Initiator - kameleon/kiemul - based on Hyrabus with HydraNFC

## Hydrabus & HydraNFC

From Benjamin VERNOUX ( @bvernoux )

- https://hydrabus.com/hydrabus-1-0-specifications/
- https://hydrabus.com/hydranfc-1-0-specifications/


## Build

This firmware is using STM32CubeIDE, compatible with STM32CubeMX

Hydrabus is using a `STM32F405`, you need its stack from ST: https://www.st.com/en/embedded-software/stm32cubef4.html

Decompress it at the root of the workspace in a `ST` directory, subdirectory named `STM32Cube_FW_F4` (without version). The structure must look like this:

```
├── README.md
├── ST
│   └── STM32Cube_FW_F4
│       ├── Documentation
│       ├── Drivers
│       ├── _htmresc
│       ├── Middlewares
│       ├── Package_license.html
│       ├── Package_license.md
│       ├── package.xml
│       ├── Projects
│       ├── Release_Notes.html
│       └── Utilities
└── st25tb_kameleon_stm32_hydrabus_hydranfc_v1
```

## Flash

You can flash the firmware from the IDE itself, but you can also use `STM32CubeProgrammer`, the GUI or the CLI.

By example for DFU mode in CLI: `STM32_Programmer_CLI --connect port=usb1 --download st25tb_kameleon_stm32_hydrabus_hydranfc_v1.hex --verify`

```
      -------------------------------------------------------------------
                       STM32CubeProgrammer v2.17.0
      -------------------------------------------------------------------



USB speed   : Full Speed (12MBit/s)
Manuf. ID   : STMicroelectronics
Product ID  : STM32  BOOTLOADER
SN          : 207036B25853
DFU protocol: 1.1
Board       : --
Device ID   : 0x0413
Device name : STM32F405xx/F407xx/F415xx/F417xx
Flash size  : 1 MBytes (default)
Device type : MCU
Revision ID : --
Device CPU  : Cortex-M4


Memory Programming ...
Opening and parsing file: st25tb_kameleon_stm32_hydrabus_hydranfc_v1.hex
  File          : st25tb_kameleon_stm32_hydrabus_hydranfc_v1.hex
  Size          : 27.13 KB
  Address       : 0x08000000


Erasing memory corresponding to segment 0:
Erasing internal memory sector 0
erasing sector 0000 @: 0x08000000 done
Erasing memory corresponding to segment 1:
Erasing internal memory sector 1
erasing sector 0001 @: 0x08004000 done
Erasing memory corresponding to segment 2:
Erasing internal memory sectors [2 3]
erasing sector 0002 @: 0x08008000 done
erasing sector 0003 @: 0x0800c000 done
Download in Progress:
██████████████████████████████████████████████████ 100%

File download complete
Time elapsed during download operation: 00:00:01.965



Verifying ...


Read progress:
██████████████████████████████████████████████████ 100%

Download verified successfully
```

### Notes

- `--erase all` can be added before `--download`
- `port=usb1` is not mandatory, you can also add a `sn=___`
  - use `STM32_Programmer_CLI --list` to be sure before...