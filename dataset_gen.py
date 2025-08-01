# 1st edition single flags only

# import subprocess
# import os
# import csv
# import tempfile

# class DatasetGenerator:
#     def __init__(self, csv_file='code_dataset.csv'):
#         # Map codes to flags
#         self.opt_level_map = {'0': '-O0', '1': '-O1', '2': '-O2', '3': '-O3', 's': '-Os'}
#         self.features = ["add", "mul", "load", "store", "call", "define", "br i1", "loops"]
#         self.csv_file = csv_file

#     def count_instruction(self, filename, keyword):
#         try:
#             if keyword == "loops":
#                 result = subprocess.check_output(
#                     r"grep -E '\b(for|while|do)\b' {} | wc -l".format(filename),
#                     shell=True
#                 )
#             else:
#                 result = subprocess.check_output(f"grep -o '{keyword}' {filename} | wc -l", shell=True)
#             return int(result.strip())
#         except:
#             return 0

#     def get_basic_block_count(self, filename):
#         try:
#             result = subprocess.check_output(f"grep -oE '^[a-zA-Z0-9_.]+:' {filename} | wc -l", shell=True)
#             return int(result.strip())
#         except:
#             return 0

#     def get_instruction_count(self, filename):
#         try:
#             result = subprocess.check_output(f"grep -E '^\\s+[a-z]' {filename} | wc -l", shell=True)
#             return int(result.strip())
#         except:
#             return 0

#     def compile_and_measure(self, c_file, opt_flag):
#         out_exec = tempfile.mktemp()
#         try:
#             subprocess.run(f"clang {opt_flag} {c_file} -o {out_exec} -lm", shell=True, check=True)
#             result = subprocess.check_output(f"/usr/bin/time -f '%e' {out_exec}", shell=True, stderr=subprocess.STDOUT)
#             exec_time = float(result.strip().splitlines()[-1])
#             return exec_time
#         except subprocess.CalledProcessError:
#             print(f"[!] Failed at {opt_flag} {c_file}")
#             return float('inf')
#         finally:
#             if os.path.exists(out_exec):
#                 os.remove(out_exec)

#     def extract_features(self, c_file):
#         ir_file = tempfile.mktemp(suffix=".ll")
#         subprocess.run(f"clang -O0 -S -emit-llvm {c_file} -o {ir_file}", shell=True, check=True)

#         feats = {}
#         for instr in self.features:
#             file_to_check = c_file if instr == "loops" else ir_file
#             feats[instr] = self.count_instruction(file_to_check, instr)

#         feats['basic_blocks'] = self.get_basic_block_count(ir_file)
#         feats['total_instructions'] = self.get_instruction_count(ir_file)

#         os.remove(ir_file)
#         return feats

#     def get_best_optimization_flag(self, c_file):
#         timings = {}
#         for code, flag in self.opt_level_map.items():
#             time_taken = self.compile_and_measure(c_file, flag)
#             timings[code] = time_taken
#         # Return the code with the best (minimum) time
#         return min(timings, key=timings.get)

    # def save_to_csv(self, feature_dict, label):
    #     header = list(feature_dict.keys()) + ['label']
    #     row = list(feature_dict.values()) + [label]

    #     file_exists = os.path.exists(self.csv_file)
    #     write_header = True

    #     if file_exists and os.path.getsize(self.csv_file) > 0:
    #         write_header = False

    #     with open(self.csv_file, 'a', newline='') as f:
    #         writer = csv.writer(f)
    #         if write_header:
    #             writer.writerow(header)
    #         writer.writerow(row)

#     def process_file(self, c_file):
#         feats = self.extract_features(c_file)
#         best_flag_code = self.get_best_optimization_flag(c_file)
#         self.save_to_csv(feats, best_flag_code)
#         print(f"[✓] Processed {c_file}, best flag code: {best_flag_code}")



# 3rd Edition
import subprocess
import os
import csv
import tempfile
import random

import random

class DatasetGenerator:
    def __init__(self, csv_file='code_dataset.csv'):
        self.opt_level_map = {'0': '-O0', '1': '-O1', '2': '-O2', '3': '-O3', 's': '-Os'}
        self.binary_flags = {'f': '-fomit-frame-pointer', 'u': '-funroll-loops'}
        self.features = ["add", "mul", "load", "store", "call", "define", "br i1", "loops"]
        self.csv_file = csv_file

        # Genetic algorithm params
        self.POPULATION_SIZE = 6
        self.MUTATION_RATE = 0.1
        self.GENERATIONS = 3


    def count_instruction(self, filename, keyword):
        try:
            if keyword == "loops":
                result = subprocess.check_output(
                    r"grep -E '\b(for|while|do)\b' {} | wc -l".format(filename),
                    shell=True
                )
            else:
                result = subprocess.check_output(f"grep -o '{keyword}' {filename} | wc -l", shell=True)
            return int(result.strip())
        except:
            return 0

    def get_basic_block_count(self, filename):
        try:
            result = subprocess.check_output(f"grep -oE '^[a-zA-Z0-9_.]+:' {filename} | wc -l", shell=True)
            return int(result.strip())
        except:
            return 0

    def get_instruction_count(self, filename):
        try:
            result = subprocess.check_output(f"grep -E '^\\s+[a-z]' {filename} | wc -l", shell=True)
            return int(result.strip())
        except:
            return 0

    def compile_and_measure(self, c_file, flag_code):
        out_exec = tempfile.mktemp()
        try:
            if len(flag_code) == 1:
                flag = self.opt_level_map[flag_code]
            elif len(flag_code) == 2:
                flag = self.opt_level_map[flag_code[0]] + ' ' + self.binary_flags[flag_code[1]]
            else:
                return float('inf')

            subprocess.run(f"clang {flag} {c_file} -o {out_exec} -lm", shell=True, check=True)
            result = subprocess.check_output(f"/usr/bin/time -f '%e' {out_exec}", shell=True, stderr=subprocess.STDOUT)
            exec_time = float(result.strip().splitlines()[-1])
            return exec_time
        except subprocess.CalledProcessError:
            print(f"[!] Failed at {flag_code} {c_file}")
            return float('inf')
        finally:
            if os.path.exists(out_exec):
                os.remove(out_exec)

    def extract_features(self, c_file):
        ir_file = tempfile.mktemp(suffix=".ll")
        # subprocess.run(f"clang -O0 -S -emit-llvm {c_file} -o {ir_file}", shell=True, check=True)
        mingw_include = r"C:\MinGW\include"
        subprocess.run(f'clang -O0 -S -emit-llvm -isystem "{mingw_include}" {c_file} -o {ir_file}',shell=True,check=True)

        feats = {}
        for instr in self.features:
            file_to_check = c_file if instr == "loops" else ir_file
            feats[instr] = self.count_instruction(file_to_check, instr)

        feats['basic_blocks'] = self.get_basic_block_count(ir_file)
        feats['total_instructions'] = self.get_instruction_count(ir_file)

        os.remove(ir_file)
        return feats
    

    def generate_initial_population(self):
        population = []

        # Single flags
        for code in random.sample(list(self.opt_level_map.keys()), k=5):
            population.append(code)

        # Combinations: O flag + binary flag (e.g., "1f")
        for _ in range(self.POPULATION_SIZE - len(population)):
            o_flag = random.choice(list(self.opt_level_map.keys()))
            bin_flag = random.choice(list(self.binary_flags.keys()))
            population.append(o_flag + bin_flag)

        return population

    def crossover(self, p1, p2):
        # Single-point crossover between flag codes
        if len(p1) == 2 and len(p2) == 2:
            return p1[0] + p2[1]
        return random.choice([p1, p2])

    def mutate(self, combo):
        # Change O flag or binary flag randomly
        if len(combo) == 2:
            return random.choice(list(self.opt_level_map.keys())) + random.choice(list(self.binary_flags.keys()))
        else:
            return random.choice(list(self.opt_level_map.keys()))


    def get_best_optimization_flag(self, c_file):
        population = self.generate_initial_population()
        best_combination = None
        best_time = float('inf')

        for _ in range(self.GENERATIONS):
            scores = [(combo, self.compile_and_measure(c_file, combo)) for combo in population]
            scores.sort(key=lambda x: x[1])
            best_combination, best_time = scores[0]

            # Selection
            selected = [combo for combo, _ in scores[:max(2, self.POPULATION_SIZE // 2)]]

            # Crossover and mutation
            new_population = []
            while len(new_population) < self.POPULATION_SIZE:
                parent1 = random.choice(selected)
                parent2 = random.choice(selected)
                child = self.crossover(parent1, parent2)
                if random.random() < self.MUTATION_RATE:
                    child = self.mutate(child)
                new_population.append(child)
            population = new_population

        return best_combination


    def save_to_csv(self, feature_dict, label):
        header = list(feature_dict.keys()) + ['label']
        row = list(feature_dict.values()) + [label]

        file_exists = os.path.exists(self.csv_file)
        write_header = True

        if file_exists and os.path.getsize(self.csv_file) > 0:
            write_header = False

        with open(self.csv_file, 'a', newline='') as f:
            writer = csv.writer(f)
            if write_header:
                writer.writerow(header)
            writer.writerow(row)
            

    def process_file(self, c_file):
        feats = self.extract_features(c_file)
        best_flag_code = self.get_best_optimization_flag(c_file)
        self.save_to_csv(feats, best_flag_code)
        print(f"[✓] Processed {c_file}, best flag code: {best_flag_code}")
        return feats 






















# 2nd edition
# import subprocess
# import os
# import csv
# import tempfile
# import random

# class DatasetGenerator:
#     def __init__(self, csv_file='code_dataset.csv'):
#         self.flag_map = {'0': '-O0', '1': '-O1', '2': '-O2', '3': '-O3', 's': '-Os'}
#         self.opt_levels = ['0', '1', '2', '3', 's']  # Define the flag keys here
#         self.csv_file = csv_file

#         # Features including loop count
#         self.features = ["add", "mul", "load", "store", "call", "define", "br i1", "loop"]

#         # Genetic algorithm params
#         self.POPULATION_SIZE = 10
#         self.MUTATION_RATE = 0.1
#         self.GENERATIONS = 5

#     def count_instruction(self, filename, keyword):
#         try:
#             if keyword == "loop":
#                 result = subprocess.check_output(f"grep -E '\\b(for|while|do)\\b' {filename} | wc -l", shell=True)
#             else:
#                 result = subprocess.check_output(f"grep -o '{keyword}' {filename} | wc -l", shell=True)
#             return int(result.strip())
#         except:
#             return 0

#     def get_basic_block_count(self, filename):
#         try:
#             result = subprocess.check_output(f"grep -oE '^[a-zA-Z0-9_.]+:' {filename} | wc -l", shell=True)
#             return int(result.strip())
#         except:
#             return 0

#     def get_instruction_count(self, filename):
#         try:
#             result = subprocess.check_output(f"grep -E '^\\s+[a-z]' {filename} | wc -l", shell=True)
#             return int(result.strip())
#         except:
#             return 0

#     def compile_and_measure(self, c_file, flag_code):
#         out_exec = tempfile.mktemp()
#         flags = ' '.join([self.flag_map[c] for c in flag_code])
#         try:
#             subprocess.run(f"clang {flags} {c_file} -o {out_exec} -lm", shell=True, check=True)
#             result = subprocess.check_output(f"/usr/bin/time -f '%e' {out_exec}", shell=True, stderr=subprocess.STDOUT)
#             exec_time = float(result.strip().splitlines()[-1])
#             return exec_time
#         except subprocess.CalledProcessError:
#             print(f"[!] Compilation failed for flag combination: {flag_code} {c_file}")
#             return float('inf')
#         finally:
#             if os.path.exists(out_exec):
#                 os.remove(out_exec)

#     def extract_features(self, c_file):
#         ir_file = tempfile.mktemp(suffix=".ll")
#         subprocess.run(f"clang -O0 -S -emit-llvm {c_file} -o {ir_file}", shell=True, check=True)

#         feats = {}
#         for instr in self.features:
#             feats[instr] = self.count_instruction(ir_file if instr != "loop" else c_file, instr)

#         feats['basic_blocks'] = self.get_basic_block_count(ir_file)
#         feats['total_instructions'] = self.get_instruction_count(ir_file)

#         os.remove(ir_file)
#         return feats

#     def get_best_optimization_flag(self, c_file):
#         # Include both single and combination flags
#         candidates = []

#         # Add single flags
#         for flag in self.opt_levels:
#             candidates.append(([flag], flag))

#         # Add combinations of 2 different flags
#         for i in range(len(self.opt_levels)):
#             for j in range(i + 1, len(self.opt_levels)):
#                 combo = [self.opt_levels[i], self.opt_levels[j]]
#                 label = f"{self.opt_levels[i]}{self.opt_levels[j]}"
#                 candidates.append((combo, label))

#         # Randomly pick up to 10 options from candidates to try
#         selected = random.sample(candidates, k=min(10, len(candidates)))

#         timings = {}
#         for flags, label in selected:
#             time_taken = self.compile_and_measure(c_file, label)
#             timings[label] = time_taken

#         return min(timings, key=timings.get)

#     def save_to_csv(self, feature_dict, label):
#         header = list(feature_dict.keys()) + ['label']
#         row = list(feature_dict.values()) + [label]
#         file_exists = os.path.exists(self.csv_file)

#         with open(self.csv_file, 'a', newline='') as f:
#             writer = csv.writer(f)
#             if not file_exists or os.path.getsize(self.csv_file) == 0:
#                 writer.writerow(header)
#             writer.writerow(row)

#     def process_file(self, c_file):
#         feats = self.extract_features(c_file)
#         best_flag = self.get_best_optimization_flag(c_file)
#         self.save_to_csv(feats, best_flag)
#         print(f"[✓] Processed {c_file}, best flag: {best_flag}")

