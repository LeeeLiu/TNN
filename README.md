# TNN

## 来源
https://github.com/Tencent/TNN

## win 10 下安装
1. 编译OpenCV3
 ```
 wget https://github.com/opencv/opencv/archive/3.4.13.zip
 unzip 3.4.13.zip
 cd opencv-3.4.13

 mkdir build
 mkdir install
 cd D:\Env\OpenCV3\opencv-3.4.13\build
 cmake -DCMAKE_INSTALL_PREFIX=../install ..

 // 添加 python37_d.lib
 // C:\Users\leeeliu\AppData\Local\Programs\Python\Python37\libs

 // 用VS打开sln文件，release模式，编译工程“install”

 // 添加OpenCV路径
 // 进入examples/mac/x86，打开CMakeList.txt
 // 在find_package(OpenCV 3 REQUIRED)之前添加 set(OpenCV_DIR "D:/Env/OpenCV3/opencv-3.4.13/install")
 ```

2. 基于摄像头的人脸配准
- 摄像头选项=ON
- 命令
 ```
  cd D:/code/TNN-master/examples/windows/x86
  set OpenCV_DIR="D:/Env/OpenCV3/opencv-3.4.13/install"
  .\build_msvc_native.bat

  cd D:/code/TNN-master/examples/windows/x86/build_msvc_native/release
  demo_x86_webcam -m  ../../../../../model   -i -1
  demo_x86_webcam -m  ../../../../../model   -v ./video/benchmark0722.mp4
  ```
 
 3. 其它
- https://github.com/Tencent/TNN/blob/master/doc/en/user/demo_en.md
- https://github.com/Tencent/TNN/issues/971
