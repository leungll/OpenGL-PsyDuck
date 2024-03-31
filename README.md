# OpenGLProject_PsyDuck
**PsyDuck**, Software Development Based on Graphics Engine course, 2020 Spring, NENU 

![maven](https://img.shields.io/badge/C-passing-red)
![maven](https://img.shields.io/badge/MinGW-compile-green)
![maven](https://img.shields.io/badge/IDE-Code%3A%3ABlocks%20-yellow)
![maven](https://img.shields.io/badge/version-v1.0-orange)
![maven](https://img.shields.io/badge/License-Apache%202.0-blue)

## 开发环境
* System: Win10
* IDE: Code::Blocks 17.12
* Compiler: MinGW
* Frame: OpenGL

## 引入资源
* `glut.h & glu.h & gl.h & windows.h`
* 可在仓库 `resource` 文件夹中引入

## 编译 & 运行
* `cd OpenGLProject_PsyDuck\PsyDuck\`
* 用 Code::Blocks 打开 `PsyDuck.cbp` 文件
* `Build and run`

## 实现功能
* 基本**卡通人物填充**
* **键盘**控制运动：
    - 利用 NormalKeys —— `Alt + 1` & `Alt + 2` 实现动画的**逆时针与顺时针旋转**
    - 利用 SpecialKeys —— `GLUT_KEY_LEFT` & `GLUT_KEY_RIGHT` 实现动画左右方向**平移运动**
* **鼠标**控制运动：利用 `glutMouseFunc` & `glutMotionFunc` 实现卡通人物在**平面**沿**任意方向自动旋转**
* 利用 `glutTimerFunc` 实现动画**颜色自动变化**
* **菜单**控制：可右键弹出菜单选择**卡通动漫人物的颜色**
* 尝试 Windows GUI 编程，实现**屏幕显示字体**
