#include<GL/glut.h>
#include<Windows.h>					// wglUseFontBitmaps是Windows系统特有的函数，所以在使用前需要加入头文件
#define MAX_CHAR 128				// ASCII字符总共只有0到127，一共128种字符

void drawString(const char* str)	// 屏幕绘制字体函数
{
	static int isFirstCall = 1;
	static GLuint lists;

	glViewport(0, 0, 600, 400);		// 设置当前的视口
	glColor3f(1.0f, 0.0f, 0.0f);	// 设置字体颜色[红色]
	glRasterPos2f(0, 0);			// glRasterPos2f(x,y)用于显示[字体]时设置字符的起始位置

	if (isFirstCall) {					// 如果是第一次调用，执行初始化

		isFirstCall = 0;				// 申请MAX_CHAR个连续的显示列表编号
		lists = glGenLists(MAX_CHAR);	// 列表初始化

		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);	// 把每个字符的绘制命令都装到对应的显示列表中
		/*
			函数说明：
			Windows系统中，可以使用wglUseFontBitmaps函数来批量的产生显示字符用的显示列表。函数有四个参数：

			第一个参数表示是HDC，学过Windows GDI的朋友应该会熟悉这个。如果没有学过，那也没关系，只要知道调用wglGetCurrentDC函数，就可以得到一个HDC。

			第二个参数表示第一个要产生的字符，因为我们要产生0到127的字符的显示列表，所以这里填0。

			第三个参数表示要产生字符的总个数，因为我们要产生0到127的字符的显示列表，总共有128个字符，我们这里填的是 MAX_CHAR(宏定义)。

			第四个参数表示第一个字符所对应显示列表的编号。假如这里填1000，则第一个字符的绘制命令将被装到第1000号显示列表，第二个字符的绘制命令将被装到第1001号显示列表，依次类推。
			我们可以先用glGenLists申请128个连续的显示列表编号，然后把第一个显示列表编号填在这里。
		*/
	}

	for (; *str != '\0'; ++str)			// 调用每个字符对应的显示列表，绘制每个字符
	{
		glCallList(lists + *str);
	}
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	// 使用 glClearColor 中指定的值设定颜色缓存区的值，即将窗口中的每一个像素设置为背景色

	drawString("Hello, World!");	// 画出“Hello, World!”

	glFlush();						// 清空OpenGL命令缓冲区，强制执行命令缓冲区中所有OpenGL函数
	/*
		补充说明：
		OpenGL内部使用渲染管线来处理命令队列，OpenGL驱动执行这些命令之前，这些命令和申明处在
		挂起状态，也就是在排队。因为渲染需要和硬件打交道，而和硬件进行交互的效率非常低，所以一
		次性处理一个大的数据块远比多次处理一个个非常小的数据块的效率高的多的多。
		屏幕上的各个像素的计算是并行处理的。
	*/
}

int main(int argc, char* argv[])
{

	glutInit(&argc, argv);							// 使用glut库需要进行初始化

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);	// GLUT_SINGLE 的意思是使用单个缓冲窗口，单个缓冲窗口的意思是所有的绘制命令都在窗口绘制的时候一次
	// 性执行.可供选择的还有GLUT_DOUBLE，这个方式实际是有一个后台缓冲缓存了所有渲染命令的结果，在全部
	// 完成时快速的和屏幕缓冲进行交换，常用于制作动画效果。

	glutCreateWindow("一支王同学在此出没！");			// 设置窗口名称
	glutPositionWindow(100, 100);					// 设置窗口的位置。(x，y)表示 该窗口左上角 相对于 电脑屏幕左上角 的相对位置。
	glutReshapeWindow(600, 400);						// 设置窗口的长和宽

	glClearColor(0.05f, 0.35f, 0.7f, 1.0f);			// 画背景这句代码是用于清屏的[并画浅蓝色]
	// 原型是  void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
	// GLclampf 是OpenGL定义的一种float数据类型 代表(0,1)之间的浮点数，使用四个GLclampf的
	// 浮点数来表示不同的颜色，和windows上的RGBA表示类似，不同的是windows使用(0,255)的整数
	// 来表示，不同的 windows能表示 255*255*255 大约 16千万 多种颜色。

	glutDisplayFunc(RenderScene);					// 设定一个渲染时的(回调)函数RenderScene，GLUT会在窗口需要作出任何绘制的时候调用这个(回调)函数
	// 在窗口的尺寸变化或者再次聚焦该窗口的时候也会调用这个回调函数

	glutMainLoop();									// 这个函数启动了GLUT框架。在这一步之前做的操作相当于设置属性，并未执行。glutMainLoop只需要被唤醒
	// 一次，然后在窗口关闭之前是会一直循环执行。它会处理所有操作系统提供的信息，键盘输入等等，直到你主动
	// 关闭程序。
	return 0;
}
