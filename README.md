# dsa_cpp
✅ Usage from the root directory \
✅  Build all . 
```
make 
```
This will:
- Create a build/ folder
- Create subfolders inside build/ corresponding to your modules (arrays/, maps/, etc.)
- Compile each .cpp into an executable in its respective build subfolder
- Makefile automatically enables parallel build using all available cores (-j option)


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

✅ Clean all executables \
To delete the entire build/ folder:
```
make clean
```

✅ How it works 
- SUBDIRS – uses find to list all subfolders in your project (excluding . and build/).
- SOURCES – collects all .cpp files in all subfolders.
- TARGETS – converts each source file path to build/<subfolder>/<filename>.
- $(BUILD)/%: %.cpp – compiles each .cpp to its corresponding executable. Creates the directory if needed.
- make → builds everything
- make clean → deletes build/



