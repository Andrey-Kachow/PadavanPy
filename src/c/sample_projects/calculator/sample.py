import sys

opererations = {
    "+": "+",
    "*": "*",
    "-": "-",
    "/": "//",
    "pow": "**"
}

if len(sys.argv) > 1 and sys.argv[1] == "--calculate":
    print(eval(" ".join(sys.argv[2:]).replace("pow", "**").replace("/", "//")))
    sys.exit()

while True:

    op1 = input()
    op = input()
    op2 = input()

    print("Answer is", str(eval(f"{op1}{opererations[op]}{op2}")) + ".")

    if input() == "no":
        break