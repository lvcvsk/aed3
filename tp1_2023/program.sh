#!/bin/bash

# Set the directory containing the test case files
echo "Enter the directory containing the test case files: "
read test_case_dir

echo "Enter directory containing executable file: "
read exec_dir


if [ ! -d "$test_case_dir" ]; then
  echo "Error: directory not found"
  exit 1
fi

# Compile the C++ program
#g++ program.cpp -o program

cd $test_case_dir

# Loop through all the .txt files in the directory
for file in $test_case_dir/*.txt
do
    echo "Running $file..."
    $exec_dir/./ej3 < "$file"
done

echo "Done."
