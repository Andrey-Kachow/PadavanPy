import sys, os, subprocess, time

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

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
    "/": "/",
    "pow": "**"
}

def print_fail():
    print(bcolors.FAIL + "FAIL" + bcolors.ENDC)

def run_utility(f, s, op):
    try:
        expected = f + opererations[op] + s
        output = subprocess.check_output(executable_agrs + ["--calculate"] + [f,op,s])
        assert expected == int(output)
    except:
        print_fail()
        print(f"Something went wrong on utility mode input: {f} {op} {s}")

def run_interactive(f, s, op):
    pass

for first_op in range(1, 10):
    for second_op in range(1, 10):
        for op in opererations:

            run_utility(first_op, second_op, op)
            run_interactive(first_op, second_op, op)


print(bcolors.OKGREEN + "PASS" + bcolors.ENDC)