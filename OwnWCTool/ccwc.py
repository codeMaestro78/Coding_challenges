#!/usr/bin/env python3
#  Here we are going to build a arg parser

import sys
import argparse

def build_parse_input():
    parser = argparse.ArgumentParser(
        description="ccwc - a custom word, line, character, and byte count tool.",
        add_help=True
    )

    parser.add_argument("-c", action="store_true", help = "Count bytes")
    parser.add_argument("-l", action= "store_true",help= "Count lines")
    parser.add_argument("-w", action = "store_true", help = "Count words")
    parser.add_argument("-m",action= "store_true",help = "Count characters")
    parser.add_argument("file", nargs="?", type = str, default = None , help = "File to process")


    return parser.parse_args()


def process_stream(stream_bytes, flags, label = ""):

    num_bytes = len(stream_bytes)

    text = stream_bytes.decode('utf-8',errors = "replace")

    # Line counts
    num_lines = text.count('\n')

    # words counts
    num_words = len(text.split())

    # character counts
    num_chars = len(text)

    if not  (flags.c or flags.l or flags.w or flags.m):
        flags.c = True
        flags.l = True
        flags.w = True
        flags.m = True


    output_parts = []

    if flags.l :
        output_parts.append(f"{num_lines:>8}")
    if flags.w:
        output_parts.append(f"{num_words:>8}")
    if flags.c:
        output_parts.append(f"{num_bytes:>8}")
    if flags.m:
        output_parts.append(f"{num_chars:>8}")


    if label:
        output_parts.append(f" {label}")

    print("".join(output_parts))



def main():
    args = build_parse_input()


    try:
        if  args.file is None:
            #  read directly from the terminal pipeline stream as bytes
            stream_bytes = sys.stdin.buffer.read()
            process_stream(stream_bytes, args, label = "")
        else:
            with open(args.file , "rb") as f:
                stream_bytes = f.read()
            process_stream(stream_bytes,args , label =args.file)

    except FileNotFoundError:
         print(f"ccwc: {args.file}: No such file or directory", file=sys.stderr)
         sys.exit(1)

    except PermissionError:
        print(f"ccwc: {args.file}: Permission denied", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()
