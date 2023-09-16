import os
import sys

from os.path import isfile, isdir

def file_exists(path):
	return os.path.exists(path)


languages = {
	".py": "Python",
	".c": "C Programming Language", 
	".h": "C header files",
	".html": "HTML",
	".kt": "Kotlin",
    ".java": "Java",
    ".css": "CSS",
    ".js": "JavaScript",
    ".sh": "Bash scripts",
    ".hs" : "Haskell",
    ".lhs": "Literate Haskell"
}

lang_stat = dict(zip(languages.keys(), [0] * len(languages)))

DIRNAME = '.'
if len(sys.argv) > 1:
    DIRNAME = sys.argv[1]


def traverse(root_dir, languages):
    for path in os.listdir(root_dir):
        path = os.path.join(root_dir, path)
        if isdir(path):
            traverse(path, languages)
        else:
            file_ex = None
            for extension in languages.keys():
                if (path.endswith(extension)):
                    file_ex = extension
                    break

            if file_ex == None:
                print("unresolved extension of", path)
                continue

            with open(path, 'r', encoding="latin-1") as f:
                count = 0
                for line in f:
                    if line.rstrip() != "":
                        lang_stat[file_ex] += 1
                        count += 1
                print(path, "-", count)

print()
traverse(DIRNAME, languages)
print()

lang_stat = dict(filter(lambda p: p[1] > 0, lang_stat.items()))

total_line_count = sum(lang_stat.values())

for (ex, lang) in languages.items():
    if (ex not in lang_stat.keys()):
        continue
    print(f"There are {lang_stat[ex]} lines of {lang} in the project, which is {round(100 * lang_stat[ex] / total_line_count)}%")
    print()

print("Total number of non empty lines is", total_line_count)

