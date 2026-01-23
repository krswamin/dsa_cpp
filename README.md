# dsa_cpp
Scratch pad for DSA interview questions
Leetcode 150: https://leetcode.com/studyplan/top-interview-150/
Leetcode 75 : https://leetcode.com/studyplan/leetcode-75/

## Module specific READMEs
- Module specific Readmes are in their respective folders such as graphs, trees etc.
- Multiple READMEs within same code base /module is not common practise, but is very useful for quick documentation , and jotting down learnings. Also helps keep Readme's small and contained topic-wise.


## Prerquisites 
✅ Install clang-format
```
sudo apt update
sudo apt install clang-format
```
✅ Install clang-tidy
```
sudo apt update
sudo apt install clang-tidy
```

✅  Install cppcheck
```
sudo apt update
sudo apt install cppcheck
```

## Usage
✅ Usage is from the root directory \

✅ Clean all executables
```
make clean
```
delete the entire build/ folder

✅  Build all 
```
make 
```
This will:
- Create a build/ folder
- Create subfolders inside build/ corresponding to your modules (arrays/, maps/, etc.)
- Compile each .cpp into an executable in its respective build subfolder
- Makefile automatically enables parallel build using all available cores (-j option)
- formats only modified files, then builds incrementally.

✅  Running the programme 
\
All executables are inside the build folder. Choose any executable of choice from the build folder. \
Example1. to run bfs on undirected graphs run
```
./build/graphs/traversal/undirected_graph_bfs
```
Example 2. To run the rotate image executable run
```
./build/graphs/matrix/rotate_image
```

### Additional Usage Details
✅  Use only some cores 

If you'd like to override to use only some cores
```
make -j8      # use 8 threads
make -j4      # use 4 threads
```

✅  Build only a single file \
You can also build a single .cpp file. \
The Makefile will create build/arrays/ if it doesn’t exist
Compile only arrays/array1.cpp into build/arrays/array1
```
make build/arrays/array1
```

✅  Formatting 
```
make format
```
formats all .cpp and .h files (full enforcement).(not just modified files)

✅  Linting
```
make lint
```
run clang-tidy on all files (not just modified files)


✅  CPP-check
```
make cppcheck
```
run cppcheck on all files (not just modified files)


✅ Clean all executables
```
make clean
```
delete the entire build/ folder

✅ Rebuild
```
make rebuild	
```
Clean + full build

✅ How it works 
- SUBDIRS – uses find to list all subfolders in your project (excluding . and build/).
- SOURCES – collects all .cpp files in all subfolders.
- TARGETS – converts each source file path to build/<subfolder>/<filename>.
- $(BUILD)/%: %.cpp – compiles each .cpp to its corresponding executable. Creates the directory if needed.
- make → builds everything
- make clean → deletes build/




