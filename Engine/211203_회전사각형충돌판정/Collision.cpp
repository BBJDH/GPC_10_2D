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

    return length(dest.Location - src.Location) <= (dest.Diameter / 2 + src.Diameter / 2);
}
bool Collide(Point const& dest, Rectangle const& src)
{
    vector<2> const min = { src.Location[0] - src.Length[0],src.Location[1] - src.Length[1] };
    vector<2> const max = { src.Location[0] + src.Length[0],src.Location[1] + src.Length[1] };

    return (min[0] <= dest.Location[0]) && (dest.Location[0] <= max[0]) && ((min[1] <= dest.Location[1]) && (dest.Location[1] <= max[1]));
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
    //사각형의 너비 합과 높이 합보다 x간격과 y간격이 더 작으면 충돌

    return ((dest.Location[0]+src.Location[0])<=sum_length[0])&& ((dest.Location[1] + src.Location[1]) <= sum_length[1]);
}
//사각형 사각형
//원 사각형

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
        if (sum < abs(dot(axes[i], distance)))  //분리축이 있다!
            return false;
    }
    return true;
}

