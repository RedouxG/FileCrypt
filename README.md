FileCrypt
=========

About
-----
Simple implementation of AES-CTR crypting using 256 bit hashed key. Hasihing is done using SHA-256. 

Program takes an input file and crypts it using a key and outputs a crypted file. Decrypting works the same way.

Encryption is done in 1MB blocks, IV is prepended in the clear for each block.

Building
--------
No additional libraries are needed, project is fully self contained.

**Windows compilation:**
1) Compile using .bat files provided:
    - `winBuildCMake.bat` builds the project using CMake and g++
    - `winBuild.bat` builds the project using g++

**Linux compilation:**
1) Work in progress (changes to dir system in the project have to be made to be compatible with unix)

Example Use
-----------
Crypting a file:
```
(.exe) crypt inputFile.txt outputFile.bin
```

Decrypting a file:
```
(.exe) decrypt inputFile.bun outputFile.txt
```

For more commands and options use:
```
(.exe) help
```