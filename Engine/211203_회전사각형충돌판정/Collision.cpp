#include "vector.h"
#include <vector>

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

    return length(dest.Location - src.Location) <= (src.Diameter / 2);
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
    return ((dest.Location[0]-src.Location[0])<=sum_length[0])&& ((dest.Location[1] - src.Location[1]) <= sum_length[1]);
}
bool Collide(Rectangle const& dest, Circle const& src)
{
    //�簢���� �ʺ���� Ȥ�� ���� ���� �ȿ� ���Դٸ�, �簢���ʺ� ���̿� r��ŭ ���� �簢���� ���� �������� �浹 ����
    //���� ������ �簢�� ������ x, y ��ǥ���� �۴ٸ� ������ �������� ���� �浹 ����
    //���� ������ �簢�� ������ x��ǥ�� ũ�� y��ǥ�� �۴ٸ� ������ �������� �浹 ����
    //���� ������ �簢�� ������ x��ǥ�� �۰� y��ǥ�� ũ�ٸ� ���� �Ʒ� �������� ���� �浹����
    //���� ������ �簢�� ������ x, y ��ǥ���� ũ�ٸ� ������ �Ʒ� �������� ���� �浹 ����

    bool isrange_x = ((dest.Location[0] - dest.Length[0]) < src.Location[0]) && (src.Location[0] < (dest.Location[0] + dest.Length[0]));
    bool isrange_y = ((dest.Length[1] - dest.Location[1]) < src.Location[0]) && (src.Location[0] < (dest.Length[0] + dest.Location[0]));

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
        rect_leftup.Location = { dest.Location[0] - dest.Length[0],dest.Location[1] - dest.Length[1] };
        return Collide(rect_leftup,src);
    }
    else  if (src.Location[0] > dest.Location[0] && src.Location[1] < dest.Location[1])//������ ��
    {
        Point rect_leftup;
        rect_leftup.Location = { dest.Location[0] + dest.Length[0],dest.Location[1] - dest.Length[1] };
        return Collide(rect_leftup, src);
    }
    else  if (src.Location[0] < dest.Location[0] && src.Location[1] > dest.Location[1])//���� �Ʒ�
    {
        Point rect_leftup;
        rect_leftup.Location = { dest.Location[0] - dest.Length[0],dest.Location[1] + dest.Length[1] };
        return Collide(rect_leftup, src);
    }
    else  if (src.Location[0] > dest.Location[0] && src.Location[1] > dest.Location[1])//������ �Ʒ�
    {
        Point rect_leftup;
        rect_leftup.Location = { dest.Location[0] + dest.Length[0],dest.Location[1] + dest.Length[1] };
        return Collide(rect_leftup, src);
    }
    return false;
}


bool Collide(Rectangle const& LHS, Rectangle const& RHS)
{
    vector<2> const distance = LHS.Location - RHS.Location;
    float constexpr radian = 3.141592653f / 180.0f;
    vector<2> const axes[4] //axis
    {
        {cos(LHS.Angle*radian),sin(LHS.Angle*radian)},     
        {-sin(LHS.Angle * radian),cos(LHS.Angle * radian)},
        {cos(LHS.Angle * radian),sin(LHS.Angle * radian)},
        {-sin(LHS.Angle * radian),cos(LHS.Angle * radian)}
    };

    vector<2> const vectors[4]
    {
        axes[0] * (LHS.Length[0] / 2),
        axes[1] * (LHS.Length[1] / 2),
        axes[2] * (RHS.Length[0] / 2),
        axes[3] * (RHS.Length[1] / 2)
    };

    for (size_t i = 0; i < 4; ++i)
    {
        float sum = 0;
        for (size_t j = 0; j < 4; ++j)
        {
            sum += abs(dot(axes[i], vectors[j]));
        }
        if (sum < abs(dot(axes[i], distance)))  //�и����� �ִ�!
            return false;
    }
    return true;
}

