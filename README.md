# Swatch Internet Time Calculator 2.0

This C program calculates Swatch Internet Time, a revolutionary concept that **could have** changed how people measure time. In this alternate reality where Internet Time became the global standard, this tool would be essential for daily time management!

Internet Time divides the day into 1000 'beats', abolishing time zones and providing a universal time for everyone.

## Features

- **Real-time Beat Calculation**: Current beat (@) based on Internet Time
- **Advanced Time Conversion**: Convert beats back to standard time
- **Multiple Output Formats**: Customizable display formats
- **Timezone Support**: Handle different timezone offsets (-12 to +14 hours)
- **Watch Mode**: Continuous real-time updates
- **Verbose Mode**: Detailed time information and context
- **Internet Date Display**: Show dates in Internet Time format
- **Local Time Support**: Use system local time instead of UTC
- **Portable & Lightweight**: Minimal dependencies, runs everywhere
- **Perfect Integration**: Works seamlessly with tmux, status bars, and scripts

## Installation

### Prerequisites

- C compiler (GCC, Clang, or similar)
- Make (optional, for easier building)

### Quick Build

```bash
git clone <repository-url>
cd internet_time
make
```

### Development Build (with debug symbols)

```bash
make debug
```

### System Installation

```bash
make install         # Install to /usr/local/bin (requires sudo)
# or
PREFIX=$HOME/.local make install  # Install to user directory
```

## Usage

### Basic Usage

```bash
# Current Internet Time
./internet_time
# Output: @347.22

# With timezone offset (+3 hours)
./internet_time -t 3
# Output: @472.45

# Using local time
./internet_time -l
# Output: @123.78
```

### Advanced Features

```bash
# Convert beats to standard time
./internet_time -b 500
# Output: @500.00 = 12:00:00 BMT (Biel Mean Time)

# Verbose output with details
./internet_time -v
# Output: Detailed time breakdown with context

# Show Internet date
./internet_time -d
# Output: Internet Date: 2024.215 (Year 2024, Day 215)

# Watch mode (updates every second)
./internet_time -w
# Output: Continuous real-time updates

# Custom format (zero-padded integer)
./internet_time -f '@%04.0f'
# Output: @0347
```

### Practical Examples

```bash
# Status bar integration
./internet_time -f '%04.0f'  # Clean format for bars

# Time zone conversion
./internet_time -t -5        # Eastern Standard Time
./internet_time -t 9         # Japan Standard Time

# Business meeting scheduler
./internet_time -v           # Get full context for scheduling
```

## Command Line Options

| Option | Description | Example |
|--------|-------------|---------|
| `-t <offset>` | Timezone offset in hours (-12 to +14) | `-t 2` |
| `-f <format>` | Custom output format | `-f '@%04.0f'` |
| `-l` | Use local time instead of UTC | `-l` |
| `-b <beats>` | Convert beats to standard time | `-b 500` |
| `-d` | Show Internet date format | `-d` |
| `-v` | Verbose output with details | `-v` |
| `-w` | Watch mode (continuous updates) | `-w` |
| `-h` | Show help | `-h` |

### Format Specifiers

- `%f` - Float beats (e.g., 347.22)
- `%d` - Integer beats (e.g., 347)
- `%3d` - Padded integer beats (e.g., 347)
- `%04d` - Zero-padded integer beats (e.g., 0347)

## Integration Examples

### tmux Status Bar

Add to your `.tmux.conf`:

```tmux
set-option -ag status-right ' #[fg=cyan,bg=default]@#(internet_time -f "%.0f")'
```

### Bash Prompt

Add to your `.bashrc`:

```bash
export PS1='[\u@\h \W @$(internet_time -f "%.0f")] \$ '
```

### Shell Script Integration

```bash
#!/bin/bash
current_beat=$(internet_time -f "%.0f")
if [ $current_beat -lt 500 ]; then
    echo "Good morning! It's @$current_beat"
else
    echo "Good evening! It's @$current_beat"
fi
```

## About Internet Time

In this alternate reality where Swatch Internet Time became the global standard:

- **No Time Zones**: Universal time for all
- **1000 Beats per Day**: Each beat = 1 minute 26.4 seconds
- **BMT Reference**: Biel Mean Time (UTC+1) as the base
- **Beat Periods**:
  - **0-249**: Morning beats
  - **250-499**: Afternoon beats
  - **500-749**: Evening beats
  - **750-999**: Night beats

## Development

### Building & Testing

```bash
make clean && make    # Clean build
make test            # Run basic tests
make debug           # Debug version
make format          # Format code
```

### Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## License

BSD 3-Clause License - see [LICENSE](LICENSE) file for details.

## Bug Reports

Report bugs to: <crg@crg.eti.br>

---

*In a world where Internet Time ruled supreme, this would be an essential tool!*

## Contributing

Contributions are welcome! Follow these steps to contribute:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -m 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Open a Pull Request.

## License

This project is licensed under the BSD 3-Clause License. See the [LICENSE](LICENSE) file for details.

