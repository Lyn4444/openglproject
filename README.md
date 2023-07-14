# openglproject
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

```
着色器使用示例 （GLSL Uniform）绘制彩色三角形，使用uniform变量的变色正方形，EBO(索引缓冲对象)

shader_v.txt shader_f.txt: 顶点着色器、片段着色器的文本文件
shader_uniform_v.txt shader_uniform_f.txt：使用uniform变量的顶点着色器、片段着色器的文本文件

Shader.h: 自定义的着色器类，包含文本文件的读取，文件流转string，再转char数组，顶点着色器、片段着色器和着色器程序对象的创建，链接

```

## 5.soil_test.cpp
```
SOIL2的配置以及纹理的读取，生成和绘制
```
