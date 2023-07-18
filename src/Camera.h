#pragma once
#include <iostream>
using namespace std;
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>


// ö�ٶ��壺ǰ�����£�����
//ǰ����ǰλ������ + Z��ĵ�λ���� * �ٶȵ�ǰλ������
//�󣺵�ǰλ������ - Z��ĵ�λ���� * �ٶȵ�ǰλ������
//�󣺵�ǰλ������ - X��ĵ�λ���� * �ٶȵ�ǰλ������
//�ң���ǰλ������ + X��ĵ�λ���� * �ٶȵ�ǰλ������
//�ϣ���ǰλ������ + Y��ĵ�λ���� * �ٶȵ�ǰλ������
//�£���ǰλ������ - Y��ĵ�λ���� * �ٶȵ�ǰλ������
enum Camera_Movement
{
    FORWARD,		            // ��ǰ           W
    BACKWARD,		            // ���           S

    LEFT,			            // ����           Q
    RIGHT,			            // ����           E

    UPWARD,			            // ����           A
    DOWNWARD		            // ����           D
};


// Ĭ�ϵ����������
const float SPEED = 2.5f;       // ��ʼ�ٶ�
const float ZOOM = 45.0f;       // �ӽǽ�ƽ��
const float SENSITIVITY = 0.1f;
// Ĭ�ϸı������λ�õĲ���
const float YAW = -90.0f;       // ����ͷ��ƫ����
const float PITCH = 0.0f;       // ����ͷ�ĸ�����

class Camera
{
public:
    // �����������
    glm::vec3 position;
    // ��Ӱ��������ռ��е�λ����ѭ��������ϵ
    // Right_X,Up_Y,Front_Z����Ӱ������ϵ�µ�x��y��z��
    glm::vec3 Front_Z;
    glm::vec3 Up_Y;
    glm::vec3 Right_X;
    // ��������ϵ�µ���������
    glm::vec3 WorldUp;

    // �����ŷ���ǣ�ƫ�����븩����
    float Yaw;
    float Pitch;
    // ������ƶ��ٶȣ���������ȣ��ӽ�
    float MoveSpeed;
    float MouseSensitivity;
    float Zoom;

    // ֻ��ҪUp_Y��Front_Z��ͨ����˵õ�Right_X������ԭ��,����Front_Z����ΪZ��ķ�����
    // ʹ��������ʼ��
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 Up_Y = glm::vec3(0.0f, 1.0f, 0.0f)) 
        :Front_Z(glm::vec3(0.0f, 0.0f, -1.0f)), MoveSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM), Yaw(YAW), Pitch(PITCH)
    {
        this->position = position;
        this->WorldUp = Up_Y;
        this->updateCameraVectors();
    };

    // ʹ�ñ�����ʼ��
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ)
        :Front_Z(glm::vec3(0.0f, 0.0f, -1.0f)), MoveSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM), Yaw(YAW), Pitch(PITCH)
    {
        this->position = glm::vec3(posX, posY, posZ);
        this->Up_Y = glm::vec3(upX, upY, upZ);
        this->updateCameraVectors();
    }

    // ��ȡ������ĵ�ǰλ��
    glm::vec3 GetPosition()
    {
        return this->position;
    }

    // ʹ��LookAt�����õ��۲����
    glm::mat4 GetViewMatrix()
    {
        // LookAt�����۲������Ժܸ�Ч�ذ�������������任���ոն���Ĺ۲�ռ�
        // ��һ���������������λ��
        // �ڶ���������������۲��Ŀ��λ�ã���Ϊposition-Ŀ��=Front_Z������Ŀ��=position+Front_Z��
        // ������λ���޹� �˴���Ϊ���������������ƶ� ���������ע����Ŀ��ǰ��
        // ��������������������ϵ�����ϵ����������������ϵ��y�ᣩ
        // (this->position + this->Front_Z)Ϊ����������ķ���ʼ��ƽ����Z�� ���ܱ�֤����������ô�ƶ������������ע����Ŀ�귽��
        return glm::lookAt(this->position, (this->position + this->Front_Z), this->Up_Y);
    }

    // �����λ�õ��ƶ����ı�position��ͨ������
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        // �ƶ��ٶ�/ÿ���ƶ�����ƥ������:�ٶ����óɳ����Ļ�������Ϊʹ�������õĲ�ͬ����Щ�˿����ƶ��ܿ죬����Щ�˻��ƶ���������Ӱ��ʹ��
        // ����deltaTime��������Ⱦ��һ֡���õ�ʱ�䣬���������ٶȶ�ȥ����deltaTimeֵ��
        // deltaTime�ܴ󣬾���ζ����һ֡����Ⱦ�����˸���ʱ�䣬������һ֡���ٶ���Ҫ��ø�����ƽ����Ⱦ����ȥ��ʱ�䣬����Ӧƽ����������ٶ�
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

    // �����λ�õ��ƶ����ı�position��ͨ�����
    // ��Ӧ����ƶ� ����Pitch��Yaw��ֵ ����������������ķ�������
    // ˮƽ�ƶ�Ӱ��ƫ����Yaw ��ֱ�ƶ�Ӱ�츩���� Pitch
    // ������һ֡����λ�ã��ڵ�ǰ֡�е�ǰ�������λ������һ֡��λ��������
    // ���ˮƽ/��ֱ���Խ����ô�����ǻ�ƫ���Ǿ͸ı�Խ��Ҳ�����������Ҫ�ƶ�����ľ���
    void ProcessMouseMovement(double xoffset, double yoffset, GLboolean constrainPitch = true)
    {
        // ƽ���ƶ� �������������
        xoffset *= this->MouseSensitivity;
        yoffset *= this->MouseSensitivity;

        // ����Pitch��Yaw��ֵ
        this->Yaw = float(xoffset);
        this->Pitch = float(yoffset);

        // �Ը����Ƕȼ������ƣ�ȷ��������ʾ���Ƕȷ�Χ�ڣ�-89.0f��89.0f��֮��
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

    // ����������ӽ�,ͨ��������
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
    // ͨ��������Pitch��ƫ����Yaw�������Եõ������ķ�������,���������������ϵ
    void updateCameraVectors()
    {
        // ��ʼ��һ���µ������front��ǰ�������,ͨ��Pitch��Yaw���µõ��ڵ�ǰ��������ϵ�µ�Front_Z
        glm::vec3 front;
        // ͨ����꣨���ֱ���ˮƽ���ƶ�Ӱ���������ƫ���ǣ���ֱ���ƶ�Ӱ��������ĸ����ǣ�
        // glm::radians���Ƕ���ת������
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        // ��һ���õ��µ�Front_Z
        Front_Z = glm::normalize(front);
        // ��������������ҵ����� ����һ��
        // ���ݵ�ǰ��������ϵ��Front_Zͨ����˵õ�Right_X
        Right_X = glm::normalize(glm::cross(Front_Z, WorldUp));
        Up_Y = glm::normalize(glm::cross(Right_X, Front_Z));
    }
};
