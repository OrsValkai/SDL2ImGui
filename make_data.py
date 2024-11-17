import os
import json
import shutil
import hashlib

# Define the file copy list file
file_hash_list_file = 'make_data_hash_list.json'

# Define the source and destination directories
src_dir = './data'
dst_dir = './bin'

# Function to generate a hash for a file
def generate_hash(file_path):
    with open(file_path, 'rb') as f:
        file_hash = hashlib.md5(f.read()).hexdigest()
    return file_hash

# Function to save the file copy list to a JSON file
def save_file_hash_list(file_hash_list):
    with open(file_hash_list_file, 'w') as f:
        json.dump(file_hash_list, f)

# Function to load the file copy list from a JSON file
def load_file_hash_list():
    if os.path.exists(file_hash_list_file):
        with open(file_hash_list_file, 'r') as f:
            file_hash_list = json.load(f)
    else:
        file_hash_list = {}
    return file_hash_list

# Function to copy files and update the file copy list
def copy_files():
    file_hash_list = load_file_hash_list()
    
    for root, dirs, files in os.walk(src_dir):
        for file in files:
            src_file_path = os.path.join(root, file)
            dst_file_path = os.path.join(dst_dir, file)
            src_file_hash = generate_hash(src_file_path)
            if src_file_hash not in file_hash_list or file_hash_list[src_file_hash] != dst_file_path:
                # Copy the file
                shutil.copyfile(src_file_path, dst_file_path)
                print(src_file_path + "->" + dst_file_path)
                # Update the file copy list
                file_hash_list[src_file_hash] = dst_file_path
    save_file_hash_list(file_hash_list)

# Call the copy_files function
copy_files()