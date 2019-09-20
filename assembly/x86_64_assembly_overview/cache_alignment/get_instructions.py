import sys

if __name__ == "__main__":
    f_name = sys.argv[1]
    with open(f_name, 'r') as f:
        lines = f.readlines()
        with open(f_name + "_instructions", 'w') as f2:
            for line in lines:
                if line:
                    f2.write(line[line.index(">:") + 2:])


