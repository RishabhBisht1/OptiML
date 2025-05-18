import subprocess
import os
import csv
import tempfile

# List of optimization levels to test
opt_levels = ['-O0', '-O1', '-O2', '-O3', '-Os']
csv_file = 'code_dataset.csv'

# Features to extract
features = [
    "add", "mul", "load", "store", "call", "define", "br i1"
]

def count_instruction(filename, keyword):
    try:
        result = subprocess.check_output(f"grep -o '{keyword}' {filename} | wc -l", shell=True)
        return int(result.strip())
    except:
        return 0

def get_basic_block_count(filename):
    try:
        result = subprocess.check_output(f"grep -oE '^[a-zA-Z0-9_.]+:' {filename} | wc -l", shell=True)
        return int(result.strip())
    except:
        return 0

def get_instruction_count(filename):
    try:
        result = subprocess.check_output(f"grep -E '^\\s+[a-z]' {filename} | wc -l", shell=True)
        return int(result.strip())
    except:
        return 0

def compile_and_measure(c_file, opt_flag):
    out_exec = tempfile.mktemp()
    try:
        subprocess.run(f"clang {opt_flag} {c_file} -o {out_exec}", shell=True, check=True)
        # Measure execution time using `time` command
        result = subprocess.check_output(f"/usr/bin/time -f '%e' {out_exec}", shell=True, stderr=subprocess.STDOUT)
        exec_time = float(result.strip().splitlines()[-1])
        return exec_time
    except subprocess.CalledProcessError as e:
        print(f"[!] Failed at {opt_flag}")
        return float('inf')
    finally:
        if os.path.exists(out_exec):
            os.remove(out_exec)

def extract_features(c_file):
    ir_file = tempfile.mktemp(suffix=".ll")
    subprocess.run(f"clang -O0 -S -emit-llvm {c_file} -o {ir_file}", shell=True, check=True)
    
    feats = {}
    for instr in features:
        feats[instr] = count_instruction(ir_file, instr)
    
    feats['basic_blocks'] = get_basic_block_count(ir_file)
    feats['total_instructions'] = get_instruction_count(ir_file)

    os.remove(ir_file)
    return feats

def get_best_optimization_flag(c_file):
    timings = {}
    for flag in opt_levels:
        time_taken = compile_and_measure(c_file, flag)
        timings[flag] = time_taken
    best_flag = min(timings, key=timings.get)
    return best_flag

def save_to_csv(feature_dict, label):
    header = list(feature_dict.keys()) + ['label']
    row = list(feature_dict.values()) + [label]
    file_exists = os.path.exists(csv_file)
    
    with open(csv_file, 'a', newline='') as f:
        writer = csv.writer(f)
        if not file_exists:
            writer.writerow(header)
        writer.writerow(row)

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 2:
        print("Usage: python3 generate_dataset.py file.c")
        exit(1)

    c_file = sys.argv[1]
    feats = extract_features(c_file)
    best_flag = get_best_optimization_flag(c_file)
    save_to_csv(feats, best_flag)
