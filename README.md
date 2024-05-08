# Swatch Internet Time Calculator

This C program calculates Swatch Internet Time, a revolutionary concept introduced by Swatch that changed how people measure time. ;) 

Internet Time divides the day into 1000 'beats', abolishing time zones and providing a universal time for everyone.

## Features

- Calculates the current beat (@) based on Internet Time
- Portable and lightweight
- Easily integrates with your status bar, tmux, and more

## Getting Started

### Prerequisites

To compile the program, you need to have a C compiler (like GCC or Clang) installed on your system.

### Compilation

You can compile the program using the provided `Makefile`. Simply run:

```bash
make
```

Alternatively, you can compile it manually:

```bash
gcc -o internet_time main.c
```

### Usage

Once compiled, you can run the program to get the current Internet Time:

```bash
./internet_time
```

### Integration with tmux

You can display the current Internet Time on your tmux status bar by adding this line to your `.tmux.conf`:

```tmux
set-option -ag status-right ' #[fg=white,bg=default]#(internet_time)'
```

Make sure `internet_time` is in your system's *PATH*.

## Contributing

Contributions are welcome! Follow these steps to contribute:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -m 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Open a Pull Request.

## License

This project is licensed under the BSD 3-Clause License. See the [LICENSE](LICENSE) file for details.

