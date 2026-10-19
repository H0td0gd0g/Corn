# Corn Agent

> ⚠️ **Work in Progress** — currently under active development.

A Windows x64 Mythic C2 agent written in C.

## Overview

Corn is a lightweight implant for the [Mythic C2 framework](https://github.com/its-a-feature/Mythic). It communicates with the Mythic TeamServer over HTTP POST method using a custom binary protocol.

## Binary Protocol

### Corn Agent -> Mythic(checkin)

Fixed header (38 bytes) followed by `taskCount` task blocks.

| Field | Offset | Size | Type | Description |
|---|---|---|---|---|
| `AgentUUID` | 0 | 36 | `CHAR[36]` | Callback identifier (UUID v4) |
| `action` | 36 | 1 | `BYTE` | checkin = 0x01 or get_tasking = 0x02 |

### Corn Agent -> Mythic(callback)

Fixed header (38 bytes) followed by `taskCount` task blocks.

| Field | Offset | Size | Type | Description |
|---|---|---|---|---|
| `callBackUUID` | 0 | 36 | `CHAR[36]` | Callback identifier (UUID v4) |
| `action` | 36 | 1 | `BYTE` | checkin = 0x01 or get_tasking = 0x02 |
| `taskCount` | 37 | 1 | `BYTE` | Number of following task blocks |

The following block repeats `taskCount` times:

| Field | Size | Type | Description |
|---|---|---|---|
| `commandType` | 1 | `BYTE` | Command type |
| `success` | 1 | `BYTE` | `0x01` = TRUE, `0x00` = FALSE |
| `size` | 4 | `SIZE_T` | Byte length of `value` |
| `value` | n | `BYTE[]` | Variable-length payload |


### Mythic -> Corn agent(checkin response)

### Mythic -> Corn agent(callback response)




## Usage

1. Install the HTTP C2 profile on your Mythic server
2. Build the agent
3. Execute on target
4. Callback appears in Mythic UI

Disclaimer

This project is intended for educational purposes and authorized security research only.

Do not use this tool against systems you do not own or have explicit written permission to test.
The author is not responsible for any damage or legal consequences resulting from misuse.
Usage must comply with all applicable local, national, and international laws.
Always obtain proper authorization before conducting any penetration testing activity.