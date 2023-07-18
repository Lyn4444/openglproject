#pragma once
#include <iostream>
using namespace std;
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>


// 枚举定义：前后，上下，左右
//前：当前位置向量 + Z轴的单位向量 * 速度当前位置向量
//后：当前位置向量 - Z轴的单位向量 * 速度当前位置向量
//左：当前位置向量 - X轴的单位向量 * 速度当前位置向量
//右：当前位置向量 + X轴的单位向量 * 速度当前位置向量
//上：当前位置向量 + Y轴的单位向量 * 速度当前位置向量
//下：当前位置向量 - Y轴的单位向量 * 速度当前位置向量
enum Camera_Movement
{
    FORWARD,		            // 向前           W
    BACKWARD,		            // 向后           S

    LEFT,			            // 向左           Q
    RIGHT,			            // 向右           E

    UPWARD,			            // 向上           A
    DOWNWARD		            // 向下           D
};


// 默认的摄像机参数
const float SPEED = 2.5f;       // 初始速度
const float ZOOM = 45.0f;       // 视角近平面
const float SENSITIVITY = 0.1f;
// 默认改变摄像机位置的参数
const float YAW = -90.0f;       // 摄像头的偏航角
const float PITCH = 0.0f;       // 摄像头的俯仰角

class Camera
{
public:
    // 摄像机的属性
    glm::vec3 position;
    // 摄影机在世界空间中的位置遵循左手坐标系
    // Right_X,Up_Y,Front_Z是摄影机坐标系下的x，y，z轴
    glm::vec3 Front_Z;
    glm::vec3 Up_Y;
    glm::vec3 Right_X;
    // 世界坐标系下的向上向量
    glm::vec3 WorldUp;

    // 摄像机欧拉角：偏航角与俯仰角
    float Yaw;
    float Pitch;
    // 摄像机移动速度，鼠标灵敏度，视角
    float MoveSpeed;
    float MouseSensitivity;
    float Zoom;

    // 只需要Up_Y和Front_Z，通过叉乘得到Right_X（右手原则）,设置Front_Z方向为Z轴的反方向
    // 使用向量初始化
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 Up_Y = glm::vec3(0.0f, 1.0f, 0.0f)) 
        :Front_Z(glm::vec3(0.0f, 0.0f, -1.0f)), MoveSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM), Yaw(YAW), Pitch(PITCH)
    {
        this->position = position;
        this->WorldUp = Up_Y;
        this->updateCameraVectors();
    };

    // 使用标量初始化
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ)
        :Front_Z(glm::vec3(0.0f, 0.0f, -1.0f)), MoveSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM), Yaw(YAW), Pitch(PITCH)
    {
        this->position = glm::vec3(posX, posY, posZ);
        this->Up_Y = glm::vec3(upX, upY, upZ);
        this->updateCameraVectors();
    }

    // 获取摄像机的当前位置
    glm::vec3 GetPosition()
    {
        return this->position;
    }

    // 使用LookAt函数得到观测矩阵
    glm::mat4 GetViewMatrix()
    {
        // LookAt创建观测矩阵可以很高效地把所有世界坐标变换到刚刚定义的观察空间
        // 第一个参数：摄像机的位置
        // 第二个参数：摄像机观测的目标位置（因为position-目标=Front_Z，所以目标=position+Front_Z）
        // 方向与位置无关 此处是为了无论摄像机如何移动 摄像机都会注视着目标前方
        // 第三个参数：世界坐标系下向上的向量（摄像机坐标系的y轴）
        // (this->position + this->Front_Z)为了让摄像机的方向始终平行于Z轴 样能保证无论我们怎么移动，摄像机都会注视着目标方向
        return glm::lookAt(this->position, (this->position + this->Front_Z), this->Up_Y);
    }

    // 摄像机位置的移动，改变position，通过键盘
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        // 移动速度/每次移动步长匹配问题:速度设置成常量的话，会因为使用者配置的不同，有些人可能移动很快，而有些人会移动很慢，很影响使用
        // 设置deltaTime储存了渲染上一帧所用的时间，并把所有速度都去乘以deltaTime值。
        // deltaTime很大，就意味着上一帧的渲染花费了更多时间，所以这一帧的速度需要变得更高来平衡渲染所花去的时间，来相应平衡摄像机的速度
        float velocity = MoveSpeed * deltaTime;
        if (direction == FORWARD)
        {
            this->position += this->Front_Z * velocity;
        }
        if (direction == BACKWARD)
        {
            this->position -= this->Front_Z * velocity;
        }
        if (direction == LEFT)
        {
            this->position -= this->Right_X * velocity;
        }
        if (direction == RIGHT)
        {
            this->position += this->Right_X * velocity;
        }
        if (direction == UPWARD)
        {
            this->position += this->Up_Y * velocity;
        }
        if (direction == DOWNWARD)
        {
            this->position -= this->Up_Y * velocity;
        }
    }

    // 摄像机位置的移动，改变position，通过鼠标
    // 响应鼠标移动 更改Pitch与Yaw的值 以用来计算摄像机的方向向量
    // 水平移动影响偏航角Yaw 竖直移动影响俯仰角 Pitch
    // 储存上一帧鼠标的位置，在当前帧中当前计算鼠标位置与上一帧的位置相差多少
    // 如果水平/竖直差别越大那么俯仰角或偏航角就改变越大，也就是摄像机需要移动更多的距离
    void ProcessMouseMovement(double xoffset, double yoffset, GLboolean constrainPitch = true)
    {
        // 平滑移动 乘以鼠标灵敏度
        xoffset *= this->MouseSensitivity;
        yoffset *= this->MouseSensitivity;

        // 更改Pitch与Yaw的值
        this->Yaw = float(xoffset);
        this->Pitch = float(yoffset);

        // 对俯仰角度加以限制，确保正常显示，角度范围在（-89.0f，89.0f）之间
        if (constrainPitch)
        {
            if (this->Pitch > 89.0f)
            {
                this->Pitch = 89.0f;
            }
            if (this->Pitch < -89.0f)
            {
                this->Pitch = -89.0f;
            }
        }

        this->updateCameraVectors();
    }

    // 缩放摄像机视角,通过鼠标滚轮
    void ProcessMouseScroll(double yoffset)
    {
        if (this->Zoom >= 1.0f && this->Zoom <= 90.0f)
        {
            this->Zoom -= float(yoffset);
        }
        if (this->Zoom <= 1.0f)
        {
            this->Zoom = 1.0f;
        }
        if (this->Zoom >= 90.0f)
        {
            this->Zoom = 90.0f;
        }
    }


private:
    // 通过俯仰角Pitch和偏航角Yaw来计算以得到真正的方向向量,并更新摄像机坐标系
    void updateCameraVectors()
    {
        // 初始化一个新的摄像机front向前方向变量,通过Pitch和Yaw重新得到在当前世界坐标系下的Front_Z
        glm::vec3 front;
        // 通过鼠标（或手柄）水平的移动影响摄像机的偏航角，竖直的移动影响摄像机的俯仰角；
        // glm::radians：角度制转弧度制
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        // 归一化得到新的Front_Z
        Front_Z = glm::normalize(front);
        // 计算出向上与向右的向量 并归一化
        // 根据当前世界坐标系和Front_Z通过叉乘得到Right_X
        Right_X = glm::normalize(glm::cross(Front_Z, WorldUp));
        Up_Y = glm::normalize(glm::cross(Right_X, Front_Z));
    }
};
