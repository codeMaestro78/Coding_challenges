# ccwc — Build Your Own `wc` Tool

A Python implementation of the Unix `wc` tool, built for the
[Coding Challenges — Build Your Own wc Tool](https://codingchallenges.fyi/challenges/challenge-wc/) challenge.

## Usage

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

## Examples

```bash
python3 ccwc.py -c test.txt
python3 ccwc.py -l test.txt
python3 ccwc.py -w test.txt
python3 ccwc.py -m test.txt
python3 ccwc.py test.txt
cat test.txt | python3 ccwc.py -l
```

`test.txt` is the sample file provided by the challenge.
