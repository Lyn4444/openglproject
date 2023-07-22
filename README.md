# openglproject：the practice project of OpenGL
## 1.openglproject.cpp
```
glfw 和 glew的使用示例
```
## 2.helloworld.cpp
```
glut的使用示例
```

## 3.pipeline_test.cpp

###### VBO：显存中的一个存储区域,存储大量的顶点属性信息，拥有唯一标识ID对应具体的VBO显存地址

###### VAO：保存所有顶点数据属性的状态结合，存储顶点数据格式和顶点数据所需的VBO对象引用，VAO没有存储顶点相关的属性数据，这些信息存储在VBO中，VAO相当于是多个VBO的引用，把一些VBO组合在一起作为一个对象统一管理


```
渲染管线的使用示例（绘制三角形）   

顶点着色器，片段着色器，VAO(顶点数组对象)，VBO(顶点缓冲对象)
```

## 4.uniform_test.cpp

##### Uniform 是一种从`CPU`中的应用向`GPU`中的着色器发送数据的方式

###### EBO：解决同一顶点多次调用的问题，与VBO类似，EBO存储的内容是顶点位置的索引indices，当需要使用重复的顶点是通过顶点的位置索引来调用顶点， 而不是对重复的顶点信息重复记录调用

`glUniform`：<br />
1）如`glUniform1f(GLint location,  GLfloat v0)`,为当前程序对象指定Uniform变量的值。第一个参数为location，是指明要更改的uniform变量的位置，剩下的是指明在指定的uniform变量中要使用的新值<br />
2)如`glUniformMatrix2fv(GLint location,  GLsizei count,  GLboolean transpose,  const GLfloat *value)`,count为指明要更改的元素个数。如果目标uniform变量不是一个数组，那么这个值应该设为1；如果是数组，则应该设置为>=1；value为指定一个具有count个数值的数组指针，用来更新指定的uniform变量。



```
着色器使用示例 （GLSL Uniform）绘制彩色三角形，使用uniform变量的变色正方形，EBO(索引缓冲对象)

shader_v.txt shader_f.txt: 顶点着色器、片段着色器的文本文件
shader_uniform_v.txt shader_uniform_f.txt：使用uniform变量的顶点着色器、片段着色器的文本文件

Shader.h: 自定义的着色器类，包含文本文件的读取，文件流转string，再转char数组，顶点着色器、片段着色器和着色器程序对象的创建，链接

```

## 5.soil_test.cpp

###### SOIL：简易 OpenGL 图像库（Simple OpenGL Image Library)的缩写，能读取图片并做出相应的处理，需要手动配置


```
SOIL2的配置以及纹理的读取，生成和绘制
```


## 6.soil_test_2.cpp

```
纹理变换（图片交替变换，纹理平移），glm配置
```

## 7.transform_3D.cpp

```
3D变换（旋转，平移，缩放），旋转的正方形，实现地月系统（大正方体模拟的 “地球”（只有自传），小正方体模拟的 “月球”（有自传+平移+公转）），glm::translate/scale/rotate：平移，缩放，旋转的使用
```

## 8.camera_test.cpp
```
摄像机的设置，通过响应键盘和鼠标改变摄像机的位置，使用LookAt得到观测矩阵，计算上下两帧的渲染时间差来平滑画面
Camera.h：摄像机配置的头文件
projection：投影矩阵，view：观察矩阵，transform：变换矩阵
欧拉角：可以表示3D空间中任何旋转的3个值。俯仰角(Pitch)：x轴；偏航角(Yaw)：y轴；滚转角(Roll)：z轴
```

## 9.light_test.cpp
```
冯氏光照模型
```
