## CVB Program

This is a command-line program that combines the utility of the `tail` and `head` command.

## Compilation

To compile this program, use the gcc compiler:

`gcc -o cvb cvb.c`

This will create an executable named cvb.

## Usage

You can run the program with various command-line arguments, the order does not matter:

`./cvb <arguments> <filename>`

- `-s <start>`: The Line to start reading from.
- `-e <end>`: The line to end reading from.
- `-v`: Enable verbose output.
- `-q`: Enable quiet mode, same as `-v` but supresses output.
- `<filename>`: The name of the file to process. If `-` or no filename is used, the program will read from stdin.

If an error occurs, the program will print an error message and exit.

## Usage Examples

`./main album.txt -e 5`

Prints the first 5 Lines from the "album.txt" file

`./main -s 12 -e 30 album.txt`

Prints Lines 12 to 30 from the "album.txt" file

`cat album.txt | ./main -s 12 -e 30`

Also prints Lines 12 to 30 from the "album.txt" file