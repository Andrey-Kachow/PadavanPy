import random
import subprocess
import time

LOG_FILE = "bigint_failures.txt"
NUM_TRIALS = 10000000

def err_log(msg):
    print(msg)
    with open(LOG_FILE, 'a') as f:
        f.write(f"{msg}\n")

def generate_hex():
    HEXs = list("0123456789abcdef")
    s = "0x"
    for i in range(random.randint(3, 400)):
        s += HEXs[random.randint(0, 15)]
    return s


def test_bigint():

    errcnt = 0
    failcnt = 0
    succcnt = 0
    hzcount = 0

    err_log("-----------------------NEW-------------------------\n")
    for x in range(NUM_TRIALS):


        if x % 1000 == 0:
            print(f"{x} tests have passed")

        h1 = generate_hex()
        h2 = generate_hex()

        op1 = int(h1, 16);
        op2 = int(h2, 16);

        # operator = "+" if random.randint(0, 1) else "-"
        operator = "+"

        if (random.randint(0, 1)):
            h1 = "-" + h1
            op1 = -op1

        if (random.randint(0, 1)):
            h2 = "-" + h2
            op2 = -op2


        h3 = None
        try:
            result_out = subprocess.check_output(['timeout', '10', './main', h1, operator, h2])

            output = result_out.decode("utf-8")


            h3 = output.split()[-1]

            op3 = 1
            if "-" in h3:
                op3 = -1
                h3 = h3[1:]

            op3 = op3 * int(h3, 16)

            if operator == "-":
                assert (op1 - op2 == op3)
            else:
                assert (op1 + op2 == op3)

            succcnt += 1
        except subprocess.CalledProcessError as e:
            err_log(f"----TEST {x + 1}----")
            failcnt += 1
            err_log("Failed Process")
            err_log(f"\n\n{e}\n\n")

            continue
        except AssertionError as e:
            err_log(f"----TEST {x + 1}----")
            err_log(f"\n{h1}\n{operator}\n{h2}\n")
            errcnt += 1
            err_log(f"+---+\n{output}\n+-----+")

            err_log(f"\n\n{e}\n\n")

            err_log(f"--> {h3}, errror!\n\n")
            err_log("\n\n\n\n\n")
        except Exception as e:
            err_log(f"----TEST {x + 1}----")

            err_log(f"\n\n\n\n\n\nn\n\n\n\n\n\n\n\n{e}\n\nXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\n\n\n\n\n\n\n\n")

            hzcount += 1
            err_log(f"--> {h3}, errror!\n\n")


    print(f"errors {errcnt} success {succcnt} hazards {hzcount} process fails {failcnt} out of {NUM_TRIALS}")

test_bigint();
