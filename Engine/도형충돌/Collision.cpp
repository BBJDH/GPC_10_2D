#include<Windows.h>
#include <vector>
#include "vector.h"

struct  struct_Rectangle
{
    vector<2> Length = { 0,0 };
    float     Angle = { 0 };
    vector<2> Location = { 0,0 };
};

bool Collide(struct_Rectangle const& LHS, struct_Rectangle const& RHS)
{
    vector<2> const distance = LHS.Location - RHS.Location;
    float constexpr radian = 3.141592653f / 180.0f;
    vector<2> const axes[4] //axis
    {
        {cos(LHS.Angle * radian),sin(LHS.Angle * radian)},
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
bool iscrash(POINT const& dest, int const size,
    std::vector<POINT*> const& rect, std::vector<double*> const& angle)
{
    struct_Rectangle player_rect, enemy_rect;
    player_rect.Angle = 0;
    player_rect.Location = { dest.x,dest.y };
    player_rect.Length = { size,size };
    if (!rect.empty())
    {
        for (size_t i = 0; i < rect.size(); i++)
        {
            enemy_rect.Angle = static_cast<float>(angle[i][1]);
            enemy_rect.Length = { size,size };
            enemy_rect.Location = { rect[i][0].x,rect[i][0].y };

            if (Collide(player_rect, enemy_rect))
                return true;
        }
    }
    return false;
}
