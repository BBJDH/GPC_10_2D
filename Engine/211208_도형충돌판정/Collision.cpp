#include "vector.h"
#include <vector>

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
bool Collide(Point const& point, Circle const& circle) 
{
    return length(point.Location - circle.Location) < (circle.Diameter / 2);
}
bool Collide(Point const& point, Rectangle const& rect)
{
    //vector<2> const min = { rect.Location[0] - rect.Length[0] / 2,rect.Location[1] - rect.Length[1] / 2 };
    //vector<2> const max = { rect.Location[0] + rect.Length[0] / 2,rect.Location[1] + rect.Length[1] / 2 };

    //return (min[0] <= point.Location[0]) && (point.Location[0] <= max[0]) && ((min[1] <= point.Location[1]) && (point.Location[1] <= max[1]));

    if (rect.Angle != 0)
    {
        return false;
    }
    else
    {
        vector<2> const distance = point.Location - rect.Location;
        return abs(distance[0]) <= rect.Length[0] / 2 and abs(distance[1]) <= rect.Length[1] / 2;
    }


}
bool Collide(Circle const& dest_circle, Circle const& src_circle)
{
    //Point dest_point;
    //Circle src_Circle;
    //dest_point.Location = dest.Location;
    //src_Circle.Diameter = src.Diameter + dest.Diameter;
    //src_Circle.Location = src.Location;
    //return Collide(dest_point, src_Circle);  //���� ������ �Լ��� ����ϴ� ���
    return Collide(Point{ dest_circle.Location }, Circle{ src_circle.Diameter + dest_circle.Diameter,src_circle.Location });
    //return length(dest_circle.Location - src_circle.Location) <= ((dest_circle.Diameter + src_circle.Diameter) / 2);
}
bool Collide(Rectangle const& dest_rect, Rectangle const& src_rect)
{
    if (abs(dest_rect.Angle - src_rect.Angle) < 0.1f)
    {
        return false;
    }
    else if(dest_rect.Angle ==0 and src_rect.Angle ==0)
    {
        return Collide
        (
            Point{ dest_rect.Location },
            Rectangle{ src_rect.Length + dest_rect.Length, 0, dest_rect.Location }
        );
    }
    else
    {
        //if ((dest_rect.Angle != 0) or (src_rect.Angle != 0))
        vector<2> const distance = dest_rect.Location - src_rect.Location;
        if (length(src_rect.Length + dest_rect.Length) / 2 < length(distance))
            return false;

        float constexpr radian = 3.141592653f / 180.0f;
        vector<2> const axes[4] //axis : �߽ɼ�
        {
            {cos(dest_rect.Angle*radian),sin(dest_rect.Angle*radian)},
            {-sin(dest_rect.Angle * radian),cos(dest_rect.Angle * radian)},
            {cos(dest_rect.Angle * radian),sin(dest_rect.Angle * radian)},
            {-sin(dest_rect.Angle * radian),cos(dest_rect.Angle * radian)}
        };

        vector<2> const vectors[4]
        {
            axes[0] * (dest_rect.Length[0] / 2),
            axes[1] * (dest_rect.Length[1] / 2),
            axes[2] * (src_rect.Length[0] / 2),
            axes[3] * (src_rect.Length[1] / 2)
        };

        for (size_t i = 0; i < 4; ++i)
        {
            float sum = 0;
            for (size_t j = 0; j < 4; ++j)
            {
                sum += abs(dot(axes[i], vectors[j]));
            }
            if (sum < abs(dot(axes[i], distance)))  //�и���(Separating Axis)�� �ִ�! ������ ����(Separating Axis Theorem, ���� SAT)
                return false;
        }
        return true;
    }
    //vector<2> const sum_length = dest_rect.Length / 2 + src_rect.Length / 2;
    //�簢���� �ʺ� �հ� ���� �պ��� x���ݰ� y������ �� ������ �浹
    //return (abs(dest_rect.Location[0]- src_rect.Location[0])<=sum_length[0])&& (abs(dest_rect.Location[1] - src_rect.Location[1]) <= sum_length[1]);
    
}
bool Collide(Rectangle const& rect, Circle const& circle)
{
    //�簢���� �ʺ���� Ȥ�� ���� ���� �ȿ� ���Դٸ�, �簢���ʺ� ���̿� r��ŭ ���� �簢���� ���� �������� �浹 ����
    //���� ������ �簢�� ������ x, y ��ǥ���� �۴ٸ� ������ �������� ���� �浹 ����
    //���� ������ �簢�� ������ x��ǥ�� ũ�� y��ǥ�� �۴ٸ� ������ �������� �浹 ����
    //���� ������ �簢�� ������ x��ǥ�� �۰� y��ǥ�� ũ�ٸ� ���� �Ʒ� �������� ���� �浹����
    //���� ������ �簢�� ������ x, y ��ǥ���� ũ�ٸ� ������ �Ʒ� �������� ���� �浹 ����

    vector<2> const min = rect.Location - rect.Length / 2;
    vector<2> const max = rect.Location + rect.Length / 2;

    bool isrange_x = ((rect.Location[0] - rect.Length[0] / 2) < circle.Location[0]) && (circle.Location[0] < (rect.Location[0] + rect.Length[0] / 2));
    bool isrange_y = ((rect.Location[1] - rect.Length[1] / 2) < circle.Location[1]) && (circle.Location[1] < (rect.Location[1] + rect.Length[1] / 2));



    if (rect.Angle != 0)
    {
        return false;
    }
    else if (isrange_x || isrange_y)
    {
        //�������̸� �簢�� �ʺ���� +r �� ��������Ʈ���� ����

        return Collide
        (
            Point    { circle.Location },
            Rectangle
            {
                       rect.Length + vector<2>(circle.Diameter,circle.Diameter),
                       rect.Angle,
                       rect.Location 
            }
        );
    }
    else
    {
        if (rect.Location[0] < circle.Location[0])
        {
            if (rect.Location[1] < circle.Location[1])return Collide(Point{vector<2>(max[0],max[1])}, circle);  //������ ��
            if (circle.Location[1] < rect.Location[1])return Collide(Point{vector<2>(max[0],min[1]) }, circle); //������ �Ʒ�
        }
        else
        {
            if (rect.Location[1] < circle.Location[1])return Collide(Point{ vector<2>(min[0],max[1]) }, circle); //���� ��
            if (circle.Location[1] < rect.Location[1])return Collide(Point{ vector<2>(min[0],min[1]) }, circle); //���� �Ʒ�
        }
    }
    //else  if (circle.Location[0] < rect.Location[0] && circle.Location[1] < rect.Location[1])//���� ��
    //{
    //    Point point_leftup;
    //    point_leftup.Location = rect.Location - rect.Length / 2;
    //    return Collide(point_leftup, circle);
    //}
    //else  if ((circle.Location[0] > rect.Location[0]) && (circle.Location[1] < rect.Location[1]))//������ ��
    //{
    //    Point point_rightup;
    //    point_rightup.Location = { rect.Location[0] + rect.Length[0] / 2,rect.Location[1] - rect.Length[1] / 2 };
    //    return Collide(point_rightup, circle);
    //}
    //else  if (circle.Location[0] < rect.Location[0] && circle.Location[1] > rect.Location[1])//���� �Ʒ�
    //{
    //    Point point_leftdown;
    //    point_leftdown.Location = { rect.Location[0] - rect.Length[0] / 2,rect.Location[1] + rect.Length[1] / 2 };
    //    return Collide(point_leftdown, circle);
    //}
    //else  if (circle.Location[0] > rect.Location[0] && circle.Location[1] > rect.Location[1])//������ �Ʒ�
    //{
    //    Point point_rightdown;
    //    point_rightdown.Location = rect.Location + rect.Length / 2;
    //    return Collide(point_rightdown, circle);
    //}
    return false;
}
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
                    //if(Collide(dest_point,circle)) //�� - ��
                    //if (Collide(dest_rect, circle)) // �簢 - ��
                    if(Collide(dest_circle,circle)) //�� - ��
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
                    //if (Collide(dest_rect, rect)) //�簢 - �簢
                    //if(Collide(dest_point,rect)) //�� - �簢
                    if(Collide(rect,dest_circle)) //�� - �簢
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
