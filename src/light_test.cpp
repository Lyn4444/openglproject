#include <iostream>
using namespace std;
#define GLEW_STATIC	
#include "Shader.h"
#include "Camera.h"
#include "LightPoint.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// 简化的光照模型：冯氏光照模型(把光源的颜色与物体的颜色值相乘，得到物体所反射的颜色,将光源显示为可见的物体(投光物)，需要给投光物单独设置一个顶点着色器和一个片元着色器。)
// 
// 冯氏光照模型由 3 个分量组成:环境(Ambient)光照,漫反射(Diffuse)光照,镜面(Specular)光照
// 环境(Ambient)光照:物体几乎永远不会是完全黑暗,需要使用环境光照常量，永远给物体一些颜色
// 漫反射(Diffuse)光照:模拟光源对物体的方向行影响，物体的某部分越是正对着光源，它就会越亮（需要测量光源光线是以什么角度接触物体表面）
// 镜面(Specular)光照:模拟有光泽物体上面出现的亮点，镜面光照的颜色相比于物体的本身颜色会更倾向于光的颜色（和漫反射光照一样，镜面光照也是依据光的方向向量和物体的法向量来决定的，但是它也依赖于观察方向，例如玩家是从什么方向看着这个片段的。通过反射法向量周围光的方向来计算反射向量。然后计算反射向量和视线方向的角度差，如果夹角越小，那么镜面光的影响就会越大）


int main()
{





	return 0;
}











