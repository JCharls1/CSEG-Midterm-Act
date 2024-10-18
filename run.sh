#!/bin/bash

# Check if the first argument is "c++"
if [ "$1" == "c++" ]; then
    # Compile the C++ program
    g++ Main.cpp -o Main.exe

    # Check if the compilation was successful
    if [ $? -eq 0 ]; then
        # Run the compiled executable
        ./Main.exe
    else
        echo "C++ compilation failed."
    fi

# Check if the first argument is "java"
elif [ "$1" == "java" ]; then
    # Compile the Java program
    javac Main.java

    # Check if the compilation was successful
    if [ $? -eq 0 ]; then
        # Run the compiled Java program
        java Main
    else
        echo "Java compilation failed."
    fi

# Check if the first argument is "python"
elif [ "$1" == "python" ]; then
    # Run the Python script
    python main.py

# If the argument is neither "c++", "java", nor "python"
else
    echo "Argument not provided or not recognized."
    echo "Usage: ./run.sh [c++ | java | python]"
fi
