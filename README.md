FileCrypt
=========

About
-----
Simple implementation of AES-CTR crypting using 256 bit hashed key. Hasihing is done using SHA-256. 

Program takes an input file and crypts it using a key and outputs a crypted file. Decrypting works the same way.

Encryption is done in 1MB blocks, IV is prepended in the clear for each block.

Building
--------
1) Compile using Visual Studio with classic c++ development tools or use any other compiler.

2) Move ```Dependencies/common-credentials``` folder into the build folder: ```(your build folder)/Data/common-credentials```

Second step can be skipped if key security check functionality is not desired.

No additional libraries are needed, project is fully self contained.

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