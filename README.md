## VSCodeWithOpenGLConfig in C 

## Note 
 `Do not delete .output directory `
 
 
 `You Application is in .output directory `
## Mac

How to use ?
    
    
` F5 Run App`

## Linux
    
 Install Library
 
 `sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev`
 
 
How to use ?
    
    
` F5 Run App`
## Window
[![MinGW](https://encrypted-tbn0.gstatic.com/images?q=tbn%3AANd9GcREEsFrL6Kv957dRSleOBm4qk7PISpJbImrbiDfmOC7K2vGCkER)](https://drive.google.com/open?id=147LGO_bCFHSqdZ6j1835qJb7XRS6-bZj)
### Download MinGW
[MinGW](https://drive.google.com/open?id=147LGO_bCFHSqdZ6j1835qJb7XRS6-bZj)

**How to use it ?**
``` 
*  Clone and Open In Vs Code
*  Create folder and set name like whatever you want
*  Create file with .c extension
*  Write Code
*  Press F5 or Run bat file 
*  the execute application is in executeFile(Folder)
*  !!DONE
```

#UsingVSCode_F5_button
**Install and config**
* create Folder Compiler in C
* copy mingw into folder Complier and Rename it "mingw64"
* copy folder include in 
>  freeglut into "C:/Compiler/mingw64/x86_64-w64-mingw32"
* copy folder lib or lin/x64 into "
>  C:/Compiler/mingw64/x86_64-w64-mingw32/lib"
* copy freeglut.dll in freeglut/bin into 
> System32 
and 
> SysWOW64 
* ** Clone This project**
* open 
> filename.c 
* Click F5 or Terminal and Start Debugging
* Done


#UsingBatFile
* **How to Use this bat file **
* ** Follow step by step below**
* **Install or Download MingGW and save it in a specific folder**
* **Download Freeglut and config it below**
* copy include and bin folder into MinGW
* go to "bin folder" and copy freeglut.dll in to System32 and SysWOW64
* **Extract the bat.(zip) and copy it into your folder**
* **Set your project name like this "main.c"**
* **Run This.bat **
* **Done**