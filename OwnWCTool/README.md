# ccwc — Build Your Own `wc` Tool

A `wc` clone built for the
[Coding Challenges — Build Your Own wc Tool](https://codingchallenges.fyi/challenges/challenge-wc/) challenge.

Two implementations: `ccwc.py` (Python) and `ccwc.cpp` (C++).

## C++ version (`ccwc.cpp`)

### Build

```bash
g++ -O3 ccwc.cpp -o ccwc
```

### Test and Run

1. Create a sample test file:

```bash
echo "Hello World\nThis is a test file for ccwc." > test.txt
```

2. Run with different flags:

Default (no flags — outputs lines, words, bytes, characters):

```bash
./ccwc test.txt
```

Count bytes (`-c`):

```bash
./ccwc -c test.txt
```

Count lines (`-l`):

```bash
./ccwc -l test.txt
```

Count words (`-w`):

```bash
./ccwc -w test.txt
```

Count characters (`-m`):

```bash
./ccwc -m test.txt
```

Combine flags (e.g. lines and words):

```bash
./ccwc -l -w test.txt
```

3. Standard input (stdin / pipeline stream):

```bash
cat test.txt | ./ccwc -l
echo "Count these words" | ./ccwc -w
```

4. Optional: make it globally accessible (system-wide command):

```bash
sudo mv ccwc /usr/local/bin/
```

Then run from any directory without `./`:

```bash
ccwc -l test.txt
```

## Python version (`ccwc.py`)

```bash
python3 ccwc.py [OPTIONS] [FILE]
```

| Option | Description |
| ------ | ----------- |
| `-c`   | Count bytes |
| `-l`   | Count lines |
| `-w`   | Count words |
| `-m`   | Count characters |
| no option | Show lines, words, bytes and characters |
| no file   | Read from standard input (pipes) |

```bash
python3 ccwc.py -c test.txt
python3 ccwc.py -l test.txt
python3 ccwc.py -w test.txt
python3 ccwc.py -m test.txt
python3 ccwc.py test.txt
cat test.txt | python3 ccwc.py -l
```

`test.txt` is the sample file provided by the challenge.
