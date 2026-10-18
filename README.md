
# Industrial Automation Gateway

A modular industrial automation gateway prototype built around a simulated industrial printer.

This project explores TCP/IP device communication, protocol integration, state management, and industrial monitoring using **C++, C#/.NET, and React**.

## Project Status

**Version:** V0.1 — Initial Printer Simulator

The current implementation provides a minimal C++ TCP server that accepts a status command and returns a simulated printer state.

The gateway, dashboard, and advanced printer behaviors are planned for future versions.

## Architecture

Planned system architecture:

```text
React Web Dashboard
        |
        v
C# / .NET Gateway API
        |
        v
Protocol Adapter Layer
        |
        v
C++ Printer Simulator
```

**Only the C++ Printer Simulator is currently implemented.**

## Implemented Features — V0.1

- C++17 TCP server using POSIX sockets
- Localhost listener on `127.0.0.1:5000`
- Basic text command handling
- `STATUS` command returning `STATE=IDLE`
- Error response for unknown commands
- Tested on Raspberry Pi Linux

## Build

### Requirements

- Linux
- C++17-compatible compiler (G++)
- Netcat for command-line testing

Compile from the repository root:

```bash
g++ -std=c++17 -Wall -Wextra -O2 \
    simulator/main.cpp \
    -o simulator/printer-simulator
```

## Run

```bash
./simulator/printer-simulator
```

Expected output:

```text
Printer Simulator V0.1
Listening on 127.0.0.1:5000
```

## Test

Open another terminal and execute:

```bash
printf 'STATUS\n' | nc -N 127.0.0.1 5000
```

Expected response:

```text
STATE=IDLE
```

Unknown commands return:

```text
ERROR=UNKNOWN_COMMAND
```

## Development Roadmap

- [x] V0.1 — Basic C++ TCP Printer Simulator
- [ ] V0.2 — Printer state machine: IDLE / RUNNING / FAULT
- [ ] V0.3 — Additional printer commands and responses
- [ ] V0.4 — TCP message framing and improved error handling
- [ ] V0.5 — C#/.NET Gateway API
- [ ] V0.6 — React monitoring dashboard
- [ ] V0.7 — Historical events and logging
- [ ] V0.8 — Docker-based deployment
- [ ] Future — Extensible industrial protocol adapters
- [ ] Future — EtherNet/IP research and integration

## Design Principles

- Modular architecture
- Separation between device simulation and gateway logic
- Small, testable development increments
- Clear distinction between simulated and real device behavior
- Local-first development and controlled network exposure

## Security and Limitations

The current simulator listens only on `127.0.0.1`.

It is an experimental prototype, **not a production-ready industrial controller**.

It does not currently provide:

- Authentication
- Encryption
- Robust TCP message framing
- Support for real industrial equipment

Do not connect it to production machinery or safety-critical systems.

## License

No license has been selected yet. All rights are reserved unless a license is added to this repository.
