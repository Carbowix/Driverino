# Driverino
A 2D car driving game that uses OpenGL & freeglut library.

## Installation
- Download [Mingw64.rar](https://drive.google.com/drive/folders/147LGO_bCFHSqdZ6j1835qJb7XRS6-bZj) & [freeglut folder](https://drive.google.com/drive/folders/1SSx3Q5YMAFLOFp56-wnAKRC-T3YsEGDd). (If you have mingw64 already, you download freeglut folder directly instead.)
- Preferrably create the following directory `C:/Compiler/` and paste the Mingw64 folder inside `Compiler` folder.
- Copy `include` & `lib` folders from `freeglut/MingGW/freeglut` folder that you downloaded and paste it into `C:/Compiler/mingw64/x86_64-w64-mingw32`
- Copy **freeglut.dll** file from `freeglut/MingGW/freeglut/bin` folder that you downloaded and paste it directly to [System32](https://nerdschalk.com/3-ways-to-open-system-32-folder-on-windows-11-or-10/) and [SysWOW64](https://www.minitool.com/news/syswow64.html) folders.
- [Download](https://github.com/Carbowix/Driverino/archive/refs/heads/main.zip) or clone the repo. via `git clone https://github.com/Carbowix/Driverino.git`

>**Note**: This project only works on VSCode and have not been experimented on any other compiling IDE.

### Using Visual Studio Code to debug
- When all the installation steps are done, Open the downloaded repo as a [folder](https://www.youtube.com/watch?v=u3PMR8voOo0) in VSCode.
- It is recommended to download the CPP extensions recommended by VSCode.
- Open `main.cpp` and press F5 to start debugging instantly if you followed the directory steps in [installation](#installation) guide.

### Extra steps for who did not follow the recommended directory path of Minggw64
- Head to `.vscode/launch.json` and make sure to edit the directory path for **"windows" -> "miDebuggerPath"** directory path to your custom path.
- Head to `RunOpenGL.bat` and change the directory also to your custom path.

>**Note**: Do not delete .output because your application gets compiled on debugging there.

### Final version
If you want a final compiled version of the project. It is recommended to run `RunOpenGL.bat` which compiles it into a final runnable `main.exe`


### Screenshots
- Main menu

<img src="./assets/images/menu.png"/>

- Gameplay

<img src="./assets/images/gameplay.png"/>

- Lose screen

<img src="./assets/images/lose.png"/>

## Credits
- Thanks to `Rath Meas` for his freeglut workspace. I don't have his git link anymore for his workspace.
- This project was heavily inspired by [Car 2D Racing freeglut](https://github.com/zunaidm/2D-Car-Race-game) by [Zunaidm](https://github.com/zunaidm)
