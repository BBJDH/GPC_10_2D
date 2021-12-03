#include "vector.h"


struct  Rectangle
{
    vector<2> Length   = {0,0};
    float     Angle = { 0 };
    vector<2> Location = {0,0};
};

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
        if (sum < abs(dot(axes[i], distance)))
            return false;
    }
    return true;
}
