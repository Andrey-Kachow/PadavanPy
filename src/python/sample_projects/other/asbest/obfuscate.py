# TODO: Check all Cherokee, Lisu Script

import sys
import os
import tempfile

ENCRYPTION_TABLE_V1 = {
  "3": "З",
  "4": "Ꮞ",  # Cherokee

  "a": "а", #
  "b": "b",
  "c": "с", #
  "d": "d",
  "e": "е", #
  "f": "f",
  "g": "ց", # Armenian
  "h": "հ", # Armenian
  "i": "\u0456", # Ukranian i
  "j": "\u0458", # Serbian 'ј'
  "k": "k",
  "l": "l",
  "m": "m",
  "n": "n",
  "o": "о", #
  "p": "р", #
  "q": "q",
  "r": "r",
  "s": "s",
  "t": "t",
  "u": "ս",
  "v": "v",
  "w": "w",
  "x": "х", #
  "y": "у", #
  "z": "z",

  "A": "А", #
  "B": "В", #
  "C": "С", #
  "D": "D",
  "E": "Е", #
  "F": "F",
  "G": "G",
  "H": "Н", #
  "I": "\u0406", # U+0406 Ukranian 'I'
  "J": "\u0408", # Serbian 'Ј'
  "K": "К", #
  "L": "Լ", # Armenian Letter 'Լ'   
  "M": "М", # 
  "N": "Ν", # Greek Nu
  "O": "О", #
  "P": "Р", #
  "Q": "Q",
  "R": "R",
  "S": "Տ", # Armenina letter 'Տ'
  "T": "Т", #
  "U": "Ս",
  "V": "V",
  "W": "W",
  "X": "Х", #
  "Y": "Y",
  "Z": "Ζ", # Greek Zetta'
}

def convert(text: str, encryption_table: dict):
    """
    Encrypt text using a character-to-character mapping.

    :param text: The input string to encrypt.
    :param encryption_table: Dictionary mapping single characters to single characters.
    :return: Encrypted string.
    """
    translation_table = str.maketrans(encryption_table)
    return text.translate(translation_table)

def main():
    if len(sys.argv) != 3:
        print("Usage: python script.py <file_path> <file_path>")
        sys.exit(1)

    file_path = sys.argv[1]
    dst_path = sys.argv[2]

    # Build translation table once
    translation_table = str.maketrans(ENCRYPTION_TABLE_V1)
    os.makedirs(os.path.dirname(dst_path), exist_ok=True)

    # Create temporary file in same directory (safer for atomic replace)
    with open(dst_path, 'w', encoding='utf-8') as dst_file:
        # Read and write in chunks (most efficient for huge files)
        with open(file_path, "r", encoding="utf-8", errors="ignore") as infile:
            while True:
                chunk = infile.read(1024 * 1024)  # 1MB chunks
                if not chunk:
                    break
                dst_file.write(chunk.translate(translation_table))

if __name__ == "__main__":
    main()