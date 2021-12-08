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
    //return Collide(dest_point, src_Circle);  //위에 서술한 함수를 사용하는 방법
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
        vector<2> const axes[4] //axis : 중심선
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
            if (sum < abs(dot(axes[i], distance)))  //분리축(Separating Axis)이 있다! 분할축 정리(Separating Axis Theorem, 이하 SAT)
                return false;
        }
        return true;
    }
    //vector<2> const sum_length = dest_rect.Length / 2 + src_rect.Length / 2;
    //사각형의 너비 합과 높이 합보다 x간격과 y간격이 더 작으면 충돌
    //return (abs(dest_rect.Location[0]- src_rect.Location[0])<=sum_length[0])&& (abs(dest_rect.Location[1] - src_rect.Location[1]) <= sum_length[1]);
    
}
bool Collide(Rectangle const& rect, Circle const& circle)
{
    //사각형의 너비범위 혹은 높이 범위 안에 들어왔다면, 사각형너비 높이에 r만큼 더한 사각형과 원의 중점과의 충돌 판정
    //원의 중점이 사각형 중점의 x, y 좌표보다 작다면 왼쪽위 꼭지점과 원의 충돌 판정
    //원의 중점이 사각형 중점의 x좌표는 크고 y좌표는 작다면 오른쪽 꼭지점과 충돌 판정
    //원의 중점이 사각형 중점의 x좌표는 작고 y좌표는 크다면 왼쪽 아래 꼭지점과 원의 충돌판정
    //원의 중점이 사각형 중점의 x, y 좌표보다 크다면 오른쪽 아래 꼭지점과 원의 충돌 판정

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
        //범위안이면 사각형 너비높이 +r 과 중점포인트와의 판정

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
            if (rect.Location[1] < circle.Location[1])return Collide(Point{vector<2>(max[0],max[1])}, circle);  //오른쪽 위
            if (circle.Location[1] < rect.Location[1])return Collide(Point{vector<2>(max[0],min[1]) }, circle); //오른쪽 아래
        }
        else
        {
            if (rect.Location[1] < circle.Location[1])return Collide(Point{ vector<2>(min[0],max[1]) }, circle); //왼쪽 위
            if (circle.Location[1] < rect.Location[1])return Collide(Point{ vector<2>(min[0],min[1]) }, circle); //왼쪽 아래
        }
    }
    //else  if (circle.Location[0] < rect.Location[0] && circle.Location[1] < rect.Location[1])//왼쪽 위
    //{
    //    Point point_leftup;
    //    point_leftup.Location = rect.Location - rect.Length / 2;
    //    return Collide(point_leftup, circle);
    //}
    //else  if ((circle.Location[0] > rect.Location[0]) && (circle.Location[1] < rect.Location[1]))//오른쪽 위
    //{
    //    Point point_rightup;
    //    point_rightup.Location = { rect.Location[0] + rect.Length[0] / 2,rect.Location[1] - rect.Length[1] / 2 };
    //    return Collide(point_rightup, circle);
    //}
    //else  if (circle.Location[0] < rect.Location[0] && circle.Location[1] > rect.Location[1])//왼쪽 아래
    //{
    //    Point point_leftdown;
    //    point_leftdown.Location = { rect.Location[0] - rect.Length[0] / 2,rect.Location[1] + rect.Length[1] / 2 };
    //    return Collide(point_leftdown, circle);
    //}
    //else  if (circle.Location[0] > rect.Location[0] && circle.Location[1] > rect.Location[1])//오른쪽 아래
    //{
    //    Point point_rightdown;
    //    point_rightdown.Location = rect.Location + rect.Length / 2;
    //    return Collide(point_rightdown, circle);
    //}
    return false;
}
//출력해보고싶어서 만들었습니다
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
                    //if(Collide(dest_point,circle)) //점 - 원
                    //if (Collide(dest_rect, circle)) // 사각 - 원
                    if(Collide(dest_circle,circle)) //원 - 원
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
                    //if (Collide(dest_rect, rect)) //사각 - 사각
                    //if(Collide(dest_point,rect)) //점 - 사각
                    if(Collide(rect,dest_circle)) //원 - 사각
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
//        if (sum < abs(dot(axes[i], distance)))  //분리축이 있다!
//            return false;
//    }
//    return true;
//}
//
