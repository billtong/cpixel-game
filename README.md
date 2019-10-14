# about
This is an simple 2d game for SDL2 and Skia library practice in CPlusPlus
# easy to run
## Windows (VS2019)
1. [sdl2 download](https://www.libsdl.org/download-2.0.php)
2. [skia set-up tutorial](https://skia.org/user/download)
3. build a new solution in Visual Studio 2019 with this repository and load libraries of sdl2 and skia
# log
- 20191010
待改进：需要把UI + Thread放在用一个header file下。目的是公用变量。每一个场景做成单独的一个header file。
- 20191011
commit1: 完成页面线程切换，从menu到level 0
- 20191014
	- 今天完成CWall，CPlayerX。
	- 需要加强Player和Wall之间Collide的判断准确性，尽可能减少线程的使用，预防ui堵塞
