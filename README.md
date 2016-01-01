## Mario Game

A simple mario inspired game made for my IUT class

### Run on OS X

```
make && ./mario
```

### Run on Windows

Open using Codeblocks (MinGW 32).

#### Cleanup and create `bin/` and `obj/` folders

```
rm -r bin obj; mkdir -p bin/Debug; find ./src -type d | xargs -I{} mkdir -p ./bin/Debug/{}; cp -R bin/Debug bin/Release; cp -R bin obj
```
