# chead
Recreating a unix command line tool head.
Head is a command line tool that displays the first n lines or bytes of a file, where the user can provide the value for n. If no file or value for n is provided then it displays the first 10 lines from the standard input.
## Compiling
```bash
make all
```
## Usage
```bash
chead/ $ echo "Hello, world" >> text.txt
chead/ $ ./chead -n2 text.txt
Hello, world
```
## Resources:
- Command-line option parsing with getopt(3) - [Youtube](https://www.youtube.com/watch?v=3KKvX-ZvhqI)
- Parsing program options using getopt - [Link](https://www.gnu.org/software/libc/manual/html_node/Getopt.html)
