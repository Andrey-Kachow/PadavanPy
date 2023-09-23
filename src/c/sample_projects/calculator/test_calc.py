import sys, os, subprocess, time

print("Running tests...")

executable_agrs = sys.argv[1:]


if not executable_agrs:
    time.sleep(5)
    print("No tests found. Try running:")
    print(">\tpython test_calc.py MyAmazingProgram.exe")
    sys.exit()


opererations = {
    "+": "+",
    "*": "*",
    "-": "-",
    "/": "//",
    "pow": "**"
}

def print_fail():
    print("FAIL")

def run_utility(f, s, op):
    answer = "error"
    try:
        expected = eval(str(f) + " " + opererations[op] + " " + str(s))
        output = subprocess.check_output(executable_agrs + ["--calculate"] + [str(f),op,str(s)])
        answer = int(output.decode("utf-8"))
        assert expected == answer
    except:
        print_fail()
        print(f"Something went wrong on utility mode input: {f} {op} {s}. You got {answer}")
        sys.exit()

count = 1
for first_op in range(1, 6):
    for second_op in range(1, 6):
        for op in opererations:
            print(f"Running Utility test {count} of 125", end=" ", flush=True)
            run_utility(first_op, second_op, op)
            print("PASS")
            count += 1

print("All cmd util tests passed. Now let's run interactive test")

content = "1\n+\n10\nyes\n2\n*\n2\nyes\n44\n/\n2\nyes\n4\npow\n4\nno\n"
output = ""

try:
    with open("temporary.txt", "w") as f:
        f.write(content)
        output = subprocess.check_output(executable_agrs, input=content.encode("utf-8")).decode("utf-8")
        assert "Answer is 11." in output, output
        assert "Answer is 4." in output, output
        assert "Answer is 22." in output, output
        assert "Answer is 256." in output, output
except Exception as e:
    print("For input:")
    print(content)
    print("\nyou had output:")
    sys.exit()

print("PASS")