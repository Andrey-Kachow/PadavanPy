import subprocess, tempfile, os, sys


SOURCE_FILE = "test_haskell.hs"

def create_source_file(test_code_entry):
    with open(SOURCE_FILE, "w") as f:
        f.write(f'''
            import H99
            main = print ({test_code_entry})
        ''')

def compile_source_file():
    subprocess.run(['ghc', '-o', 'actual', 'H99.hs', SOURCE_FILE], stdout=subprocess.DEVNULL)

def run_compiled_binary_and_print_actual():
    cmd = "./actual"
    ps = subprocess.Popen(cmd,shell=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
    output = ps.communicate()[0].decode("utf-8")
    print("        Actually got:", output)

def print_actual(test_code):
    create_source_file(test_code.split(" == ")[0])
    compile_source_file()
    run_compiled_binary_and_print_actual()

def run_test(test_code):
    fail = False
    with tempfile.NamedTemporaryFile(mode="wt") as f:
        f.write(f"{test_code}\n")
        f.flush()

        cmd = f"cat {f.name}  | ghci H99.hs"
        ps = subprocess.Popen(cmd,shell=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
        output = ps.communicate()[0].decode("utf-8")

        if 'output' in sys.argv:
            print(output)

        if 'True' not in output:
            print(f"FAIL :: {test_code}")
            if 'False' in output:
                print_actual(test_code)
            else:
                print("Didn't compile")
            print()
            fail = True
    return not fail


def cleanup():
    for f in [
        'actual',
        'H99.hi',
        'H99.o',
        'test_haskell.hs',
        'test_haskell.o',
        'test_haskell.hi'
    ]:
        try:
            os.remove(f)
        except FileNotFoundError as e:
            pass


with open("tests.txt") as testfile:
    test_pass = True

    if 'last' in sys.argv:

        test_codes = testfile.read().split("\n")
        test_codes.reverse()
        i = 1
        while test_codes[i]:
            if not run_test(test_codes[i]):
                test_pass = False
            i += 1
    else:
        line_count = 1
        for line in testfile.readlines():
            if line == '\n':
                line_count += 1
                continue
            if not run_test(line[:-1]):
                test_pass = False
            line_count += 1

    if test_pass:
        print("pass")
cleanup()
