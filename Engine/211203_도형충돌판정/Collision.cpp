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
bool Collide(Point const& dest, Circle const& src) 
{
    float length_temp = length(dest.Location - src.Location);
    float rad = (src.Diameter / 2);
    if (length(dest.Location - src.Location) < (src.Diameter / 2))
        return true;
    return false;

    //return length(dest.Location - src.Location) < (src.Diameter / 2);
}
bool Collide(Circle const& dest, Circle const& src)
{
    //Point dest_point;
    //Circle src_Circle;
    //dest_point.Location = dest.Location;
    //src_Circle.Diameter = src.Diameter + dest.Diameter;
    //src_Circle.Location = src.Location;
    //return Collide(dest_point, src_Circle);  //���� ������ �Լ��� ����ϴ� ���
    return length(dest.Location - src.Location) <= (dest.Diameter / 2 + src.Diameter / 2);
}
bool Collide(Point const& dest, Rectangle const& src)
{
    vector<2> const min = { src.Location[0] - src.Length[0],src.Location[1] - src.Length[1] };
    vector<2> const max = { src.Location[0] + src.Length[0],src.Location[1] + src.Length[1] };

    return (min[0] <= dest.Location[0]) && (dest.Location[0] <= max[0]) && ((min[1] <= dest.Location[1]) && (dest.Location[1] <= max[1]));
}
bool Collide(Rectangle const& dest, Rectangle const& src)
{
    vector<2> const sum_length = { dest.Length[0] + src.Length[0],dest.Length[1] + src.Length[1] };
    //�簢���� �ʺ� �հ� ���� �պ��� x���ݰ� y������ �� ������ �浹
    return (abs(dest.Location[0]-src.Location[0])<=sum_length[0])&& (abs(dest.Location[1] - src.Location[1]) <= sum_length[1]);
}
bool Collide(Rectangle const& dest, Circle const& src)
{
    //�簢���� �ʺ���� Ȥ�� ���� ���� �ȿ� ���Դٸ�, �簢���ʺ� ���̿� r��ŭ ���� �簢���� ���� �������� �浹 ����
    //���� ������ �簢�� ������ x, y ��ǥ���� �۴ٸ� ������ �������� ���� �浹 ����
    //���� ������ �簢�� ������ x��ǥ�� ũ�� y��ǥ�� �۴ٸ� ������ �������� �浹 ����
    //���� ������ �簢�� ������ x��ǥ�� �۰� y��ǥ�� ũ�ٸ� ���� �Ʒ� �������� ���� �浹����
    //���� ������ �簢�� ������ x, y ��ǥ���� ũ�ٸ� ������ �Ʒ� �������� ���� �浹 ����

    bool isrange_x = ((dest.Location[0] - dest.Length[0]) < src.Location[0]) && (src.Location[0] < (dest.Location[0] + dest.Length[0]));
    bool isrange_y = ((dest.Location[1] - dest.Length[1]) < src.Location[1]) && (src.Location[1] < (dest.Location[0] + dest.Length[0]));

    if (isrange_x || isrange_y)
    {
        //�������̸� �簢�� �ʺ���� +r �� ��������Ʈ���� ����
        Rectangle dest_rect;
        Point src_point;
        dest_rect.Angle = 0;
        dest_rect.Location = dest.Location;
        dest_rect.Length = { dest.Length[0] + (src.Diameter / 2),dest.Length[1] + (src.Diameter / 2) };
        src_point.Location = src.Location;
        return Collide( src_point, dest_rect );
    }
    else  if (src.Location[0] < dest.Location[0] && src.Location[1] < dest.Location[1])//���� ��
    {
        Point rect_leftup;
        rect_leftup.Location = dest.Location - dest.Length;
        //return Collide(rect_leftup,src);
        return length(rect_leftup.Location - src.Location) < src.Diameter / 2;
    }
    else  if ((src.Location[0] > dest.Location[0]) && (src.Location[1] < dest.Location[1]))//������ ��
    {
        Point rect_rightup;
        rect_rightup.Location = { dest.Location[0] + dest.Length[0],dest.Location[1] - dest.Length[1] };
        //return Collide(rect_rightup, src);
        return length(rect_rightup.Location - src.Location) < src.Diameter / 2;

    }
    else  if (src.Location[0] < dest.Location[0] && src.Location[1] > dest.Location[1])//���� �Ʒ�
    {
        Point rect_leftdown;
        rect_leftdown.Location = { dest.Location[0] - dest.Length[0],dest.Location[1] + dest.Length[1] };
        //return Collide(rect_leftdown, src);
        return length(rect_leftdown.Location - src.Location) < src.Diameter / 2;

    }
    else  if (src.Location[0] > dest.Location[0] && src.Location[1] > dest.Location[1])//������ �Ʒ�
    {
        Point rect_rightdown;
        rect_rightdown.Location = dest.Location + dest.Length;
        return Collide(rect_rightdown, src);
        //return length(rect_rightdown.Location - src.Location) < src.Diameter / 2;

    }
    return false;
}
//����غ���; ��������ϴ�
bool iscrash(int const& dest_x, int const& dest_y, int const dest_size,
    std::vector<int*> const& shape_pos, std::vector<double*> const& angle)
{
    Rectangle dest_rect;
    dest_rect.Location = { dest_x,dest_y };
    dest_rect.Angle = 0;
    dest_rect.Length = { dest_size ,dest_size };
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
                    //return Collide(dest_rect, circle);
                    //if (Collide(dest_rect, circle))
                    //if(Collide(dest_point,circle))
                    if(Collide(dest_circle,circle))
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
                    rect.Length = { shape_pos[i][4],shape_pos[i][5] };
                    //return Collide(dest_rect, rect);
                    //if (Collide(dest_rect, rect))
                    //if(Collide(dest_point,rect))
                    if(Collide(rect,dest_circle))
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
