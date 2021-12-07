#include "vector.h"
#include <vector>
//#include <math.h>
enum Shape_name
{
    circle = 1, rect,
};

struct Point final
{   
    vector<2> Location = { 0,0 };
};
struct Circle final
{
    float Diameter = { 0 };
    vector<2> Location = { 0,0 };
};
struct  Rectangle
{
    vector<2> Length   = {0,0};
    float     Angle = { 0 };
    vector<2> Location = {0,0};
};

#pragma region �򸲾�
bool Collide(Point const& LHS, Circle const& RHS)
{
    return length(LHS.Location - RHS.Location) <= RHS.Diameter / 2;
}

bool Collide(Point const& LHS, Rectangle const& RHS)
{
    return LHS.Location[1] <= (RHS.Location[1] - (RHS.Length[1] / 2))
        && LHS.Location[1] >= (RHS.Location[1] + (RHS.Length[1] / 2))
        && LHS.Location[0] >= (RHS.Location[0] - (RHS.Length[0] / 2))
        && LHS.Location[0] <= (RHS.Location[0] + (RHS.Length[0] / 2));
}

bool Collide(Circle const& LHS, Circle const& RHS)
{
    return length(LHS.Location - RHS.Location) <= (LHS.Diameter / 2 + RHS.Diameter / 2);
}

bool Collide(Circle const& LHS, Rectangle const& RHS)
{

    Point pRHSLeftTop;
    Point pRHSRightTop;
    Point pRHSLeftBottom;
    Point pRHSRightBottom;

    pRHSLeftTop.Location
        = { RHS.Location[0] - (RHS.Length[0] + LHS.Diameter) / 2	//��
          , RHS.Location[1] - (RHS.Length[1] + LHS.Diameter) / 2 };	//��
    pRHSRightTop.Location
        = { RHS.Location[0] + (RHS.Length[0] + LHS.Diameter) / 2	//��
          , RHS.Location[1] - (RHS.Length[1] + LHS.Diameter) / 2 };	//��
    pRHSLeftBottom.Location
        = { RHS.Location[0] - (RHS.Length[0] + LHS.Diameter) / 2	//��
          , RHS.Location[1] + (RHS.Length[1] + LHS.Diameter) / 2 };	//��
    pRHSRightBottom.Location
        = { RHS.Location[0] + (RHS.Length[0] + LHS.Diameter) / 2	//��
          , RHS.Location[1] + (RHS.Length[1] + LHS.Diameter) / 2 };	//��


    if (LHS.Location[0] >= pRHSLeftTop.Location[0]
        && LHS.Location[0] <= pRHSRightTop.Location[0])
    {
        return LHS.Location[1] >= pRHSLeftTop.Location[1]
            || LHS.Location[1] <= pRHSLeftBottom.Location[1];
    }

    if (LHS.Location[1] >= pRHSLeftTop.Location[1]
        && LHS.Location[1] <= pRHSLeftBottom.Location[1])
    {
        return LHS.Location[0] >= pRHSLeftTop.Location[0]
            || LHS.Location[0] <= pRHSRightTop.Location[0];
    }

    if (LHS.Location[0] < pRHSLeftTop.Location[0] && LHS.Location[1] < pRHSLeftTop.Location[1])
    {

        return LHS.Location[0] == pRHSLeftTop.Location[0] && LHS.Location[1] == pRHSLeftTop.Location[1];
    }

    if (LHS.Location[0] > pRHSRightTop.Location[0] && LHS.Location[1] < pRHSLeftTop.Location[1])
    {
        return LHS.Location[0] == pRHSRightTop.Location[0] && LHS.Location[1] == pRHSRightTop.Location[1];
    }

    if (LHS.Location[0] < pRHSLeftTop.Location[0] && LHS.Location[1] > pRHSLeftBottom.Location[1])
    {
        return LHS.Location[0] == pRHSLeftTop.Location[0] && LHS.Location[1] == pRHSLeftBottom.Location[1];
    }

    if (LHS.Location[0] > pRHSRightTop.Location[0] && LHS.Location[1] > pRHSLeftBottom.Location[1])
    {
        return LHS.Location[0] == pRHSRightTop.Location[0] && LHS.Location[1] == pRHSRightTop.Location[1];
    }
    return false;
}


#pragma endregion
#pragma region �ο�
                //
//bool Collide(Point const& LHS, Circle const& RHS)
//{
//    //������ ���� ������ �� �Ÿ��� ���� ���������� �۰ų� ������ �浹
//    return length(LHS.Location - RHS.Location) <= RHS.Diameter / 2;
//}
//
//bool Collide(Point const& LHS, Rectangle const& RHS)
//{
//    //�簢���� min, max ��ǥ�� ����
//    //�簢���� ���� x��ǥ���� x�� ���� �ݸ�ŭ ����, y��ǥ���� y�� ���� �ݸ�ŭ ��
//    vector<2> const min = { RHS.Location[0] - (RHS.Length[0] / 2), RHS.Location[1] - (RHS.Length[1] / 2) };
//    vector<2> const max = { RHS.Location[0] + (RHS.Length[0] / 2), RHS.Location[1] + (RHS.Length[1] / 2) };
//
//    //�簢 ���� �ȿ� ���� �ִٸ� �浹
//    return (min[0] <= LHS.Location[0]) && (LHS.Location[0] <= max[0]) && ((min[1] <= LHS.Location[1]) && (LHS.Location[1] <= max[1]));
//}
//
//bool Collide(Circle const& LHS, Circle const& RHS)
//{
//    //�º��� ������ �캯���� �캯�� ������ �� ���̰� �º� �������� �캯 �������� �պ��� �۰ų� ������ �浹
//    return length(LHS.Location - RHS.Location) <= (LHS.Diameter / 2) + (RHS.Diameter / 2);
//}
//
////bool Collide(Circle const& LHS, Rectangle const& RHS)
////{
////    //���� ������ ��ŭ �簢���� Ȯ���� ��, ���� ������ �� �簢�� �ȿ� �ִٸ� �浹
////    //���ܷ� �밢���� �������� �簢�� ���������� �� �ȿ� �ִ��� Ȯ��(���� �� �浹)
////    vector<2> const distance = { LHS.Location[0] - RHS.Location[0], LHS.Location[1] - RHS.Location[1] };
////
////    if (distance[1] > ((RHS.Length[0] / 2) + (LHS.Diameter / 2))) { return false; }
////    if (distance[2] > ((RHS.Length[1] / 2) + (LHS.Diameter / 2))) { return false; }
////
////    if (distance[1] <= ((RHS.Length[0] / 2) + (LHS.Diameter / 2))) { return true; }
////    if (distance[2] <= ((RHS.Length[1] / 2) + (LHS.Diameter / 2))) { return true; }
////
////    //????.... �̤�
////    //vector<2> const min = { RHS.Location[0] - (RHS.Length[0] / 2) - (LHS.Diameter / 2), RHS.Location[1] - (RHS.Length[1] / 2) - (LHS.Diameter / 2) };
////    //vector<2> const max = { RHS.Location[0] + (RHS.Length[0] / 2) + (LHS.Diameter / 2), RHS.Location[1] + (RHS.Length[1] / 2) + (LHS.Diameter / 2) };
////
////    //���⼭ ���� �� �𸣰ڽ��ϴ�.... �̤�
////
////}
//
//bool Collide(Rectangle const& LHS, Rectangle const& RHS)
//{
//    //�������� ���� ���ϱ� ���� ������ ���ֱ�
//    vector<2> const distance = LHS.Location - RHS.Location;		//LHS �º� , RHS �캯
//
//    //distance[0]�� x ����, [1]�� y����
//
//    float constexpr radian = 3.141592653f / 180.0f;
//
//    //�� ���� ���� ���ϱ�, axis�� ����(���̶�� ��)
//    vector<2> const axes[4]
//    {
//        { cos(LHS.Angle * radian), sin(LHS.Angle * radian)},
//        {-sin(LHS.Angle * radian), cos(LHS.Angle * radian)},
//        { cos(RHS.Angle * radian), sin(RHS.Angle * radian)},
//        {-sin(RHS.Angle * radian), cos(RHS.Angle * radian)}
//    };
//
//    //vector<2>�� float ���� 2���� ���� �迭�� ���ٰ� �����ϸ� ��.
//    vector<2> const vectors[4]
//    {
//        //LHS.Length[0] -> x ����, LHS.Length[1] -> y ����
//        axes[0] * (LHS.Length[0] / 2),
//        axes[1] * (LHS.Length[1] / 2),
//        axes[2] * (RHS.Length[0] / 2),
//        axes[3] * (RHS.Length[1] / 2)
//    };
//
//    for (int i = 0; i < 4; ++i)
//    {
//        float sum = 0;
//
//        //��� ���Ϳ� ���� �翵�� ������
//        for (int j = 0; j < 4; ++j)
//            sum += abs(dot(axes[i], vectors[j]));
//
//        //���� ���� ������ �Ÿ��� ���밪
//        if (sum < abs(dot(axes[i], distance)))
//            return false;
//    }
//
//    return true;
//}  
#pragma endregion

//����غ���; ��������ϴ�
bool iscrash(int const& dest_x, int const& dest_y, int const dest_size,
    std::vector<int*> const& shape_pos, std::vector<double*> const& angle)
{
    Rectangle dest_rect;
    dest_rect.Location = { dest_x,dest_y };
    dest_rect.Angle = 0;
    dest_rect.Length = { dest_size*2 ,dest_size*2 };
    Circle dest_circle;
    dest_circle.Location = { dest_x,dest_y };
    dest_circle.Diameter = static_cast<float>(dest_size) * 2;
    Point dest_point;
    dest_point.Location = { dest_x,dest_y };
    if (!shape_pos.empty())
    {
        for (size_t i = 0; i < shape_pos.size(); i++)
        {
            if (shape_pos[i][0] == 0)
            {
                switch (shape_pos[i][1])
                {
                case circle:
                {
                    Circle circle;
                    circle.Location = { shape_pos[i][2],shape_pos[i][3] };
                    circle.Diameter = static_cast<float>(shape_pos[i][4]) * 2;
                    //if (Collide(dest_rect, circle)) // �簢 - ��
                    //if(Collide(dest_circle,circle)) //�� - ��
                    if(Collide(dest_point,circle)) //�� - ��
                    {
                        shape_pos[i][0] = 1;
                        return true;
                    }
                    break;
                }
                case rect:
                {
                    Rectangle rect;
                    rect.Location = { shape_pos[i][2],shape_pos[i][3] };
                    rect.Angle = 0;
                    rect.Length = { shape_pos[i][4]*2,shape_pos[i][5]*2 };
                    //return Collide(dest_rect, rect);
                    //if(Collide(rect,dest_circle)) //�� - �簢
                    //if (Collide(dest_rect, rect)) //�簢 - �簢
                    if(Collide(dest_point,rect)) //�� - �簢
                    {
                        shape_pos[i][0] = 1;
                        return true;
                    }
                    break;
                }
                }
            }
        }
    }
    return false;
}


//bool Collide(Rectangle const& LHS, Rectangle const& RHS)
//{
//    vector<2> const distance = LHS.Location - RHS.Location;
//    float constexpr radian = 3.141592653f / 180.0f;
//    vector<2> const axes[4] //axis
//    {
//        {cos(LHS.Angle*radian),sin(LHS.Angle*radian)},     
//        {-sin(LHS.Angle * radian),cos(LHS.Angle * radian)},
//        {cos(LHS.Angle * radian),sin(LHS.Angle * radian)},
//        {-sin(LHS.Angle * radian),cos(LHS.Angle * radian)}
//    };
//
//    vector<2> const vectors[4]
//    {
//        axes[0] * (LHS.Length[0] / 2),
//        axes[1] * (LHS.Length[1] / 2),
//        axes[2] * (RHS.Length[0] / 2),
//        axes[3] * (RHS.Length[1] / 2)
//    };
//
//    for (size_t i = 0; i < 4; ++i)
//    {
//        float sum = 0;
//        for (size_t j = 0; j < 4; ++j)
//        {
//            sum += abs(dot(axes[i], vectors[j]));
//        }
//        if (sum < abs(dot(axes[i], distance)))  //�и����� �ִ�!
//            return false;
//    }
//    return true;
//}
//
