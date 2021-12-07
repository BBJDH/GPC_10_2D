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

#pragma region 평림씨
//bool Collide(Point const& LHS, Circle const& RHS)
//{
//    return length(LHS.Location - RHS.Location) <= RHS.Diameter / 2;
//}
//
//bool Collide(Point const& LHS, Rectangle const& RHS)
//{
//    return LHS.Location[1] <= (RHS.Location[1] - (RHS.Length[1] / 2))
//        && LHS.Location[1] >= (RHS.Location[1] + (RHS.Length[1] / 2))
//        && LHS.Location[0] >= (RHS.Location[0] - (RHS.Length[0] / 2))
//        && LHS.Location[0] <= (RHS.Location[0] + (RHS.Length[0] / 2));
//}
//
//bool Collide(Circle const& LHS, Circle const& RHS)
//{
//    return length(LHS.Location - RHS.Location) <= (LHS.Diameter / 2 + RHS.Diameter / 2);
//}
//
//bool Collide(Circle const& LHS, Rectangle const& RHS)
//{
//
//    Point pRHSLeftTop;
//    Point pRHSRightTop;
//    Point pRHSLeftBottom;
//    Point pRHSRightBottom;
//
//    pRHSLeftTop.Location
//        = { RHS.Location[0] - (RHS.Length[0] + LHS.Diameter) / 2	//좌
//          , RHS.Location[1] - (RHS.Length[1] + LHS.Diameter) / 2 };	//상
//    pRHSRightTop.Location
//        = { RHS.Location[0] + (RHS.Length[0] + LHS.Diameter) / 2	//우
//          , RHS.Location[1] - (RHS.Length[1] + LHS.Diameter) / 2 };	//상
//    pRHSLeftBottom.Location
//        = { RHS.Location[0] - (RHS.Length[0] + LHS.Diameter) / 2	//좌
//          , RHS.Location[1] + (RHS.Length[1] + LHS.Diameter) / 2 };	//하
//    pRHSRightBottom.Location
//        = { RHS.Location[0] + (RHS.Length[0] + LHS.Diameter) / 2	//우
//          , RHS.Location[1] + (RHS.Length[1] + LHS.Diameter) / 2 };	//하
//
//
//    if (LHS.Location[0] >= pRHSLeftTop.Location[0]
//        && LHS.Location[0] <= pRHSRightTop.Location[0])
//    {
//        return LHS.Location[1] >= pRHSLeftTop.Location[1]
//            || LHS.Location[1] <= pRHSLeftBottom.Location[1];
//    }
//
//    if (LHS.Location[1] >= pRHSLeftTop.Location[1]
//        && LHS.Location[1] <= pRHSLeftBottom.Location[1])
//    {
//        return LHS.Location[0] >= pRHSLeftTop.Location[0]
//            || LHS.Location[0] <= pRHSRightTop.Location[0];
//    }
//
//    if (LHS.Location[0] < pRHSLeftTop.Location[0] && LHS.Location[1] < pRHSLeftTop.Location[1])
//    {
//
//        return LHS.Location[0] == pRHSLeftTop.Location[0] && LHS.Location[1] == pRHSLeftTop.Location[1];
//    }
//
//    if (LHS.Location[0] > pRHSRightTop.Location[0] && LHS.Location[1] < pRHSLeftTop.Location[1])
//    {
//        return LHS.Location[0] == pRHSRightTop.Location[0] && LHS.Location[1] == pRHSRightTop.Location[1];
//    }
//
//    if (LHS.Location[0] < pRHSLeftTop.Location[0] && LHS.Location[1] > pRHSLeftBottom.Location[1])
//    {
//        return LHS.Location[0] == pRHSLeftTop.Location[0] && LHS.Location[1] == pRHSLeftBottom.Location[1];
//    }
//
//    if (LHS.Location[0] > pRHSRightTop.Location[0] && LHS.Location[1] > pRHSLeftBottom.Location[1])
//    {
//        return LHS.Location[0] == pRHSRightTop.Location[0] && LHS.Location[1] == pRHSRightTop.Location[1];
//    }
//    return false;
//}
//

#pragma endregion
#pragma region 민영
                //
//bool Collide(Point const& LHS, Circle const& RHS)
//{
//    //점에서 원의 중점을 뺀 거리가 원의 반지름보다 작거나 같으면 충돌
//    return length(LHS.Location - RHS.Location) <= RHS.Diameter / 2;
//}
//
//bool Collide(Point const& LHS, Rectangle const& RHS)
//{
//    //사각형의 min, max 좌표를 구함
//    //사각형의 중점 x좌표에서 x축 길이 반만큼 빼고, y좌표에서 y축 길이 반만큼 뺌
//    vector<2> const min = { RHS.Location[0] - (RHS.Length[0] / 2), RHS.Location[1] - (RHS.Length[1] / 2) };
//    vector<2> const max = { RHS.Location[0] + (RHS.Length[0] / 2), RHS.Location[1] + (RHS.Length[1] / 2) };
//
//    //사각 범위 안에 점이 있다면 충돌
//    return (min[0] <= LHS.Location[0]) && (LHS.Location[0] <= max[0]) && ((min[1] <= LHS.Location[1]) && (LHS.Location[1] <= max[1]));
//}
//
//bool Collide(Circle const& LHS, Circle const& RHS)
//{
//    //좌변의 중점과 우변에서 우변의 중점을 뺀 길이가 좌변 반지름과 우변 반지름의 합보다 작거나 같으면 충돌
//    return length(LHS.Location - RHS.Location) <= (LHS.Diameter / 2) + (RHS.Diameter / 2);
//}
//
////bool Collide(Circle const& LHS, Rectangle const& RHS)
////{
////    //원의 반지름 만큼 사각형을 확장한 후, 원의 중점이 그 사각형 안에 있다면 충돌
////    //예외로 대각선에 있을때는 사각형 꼭지점들이 원 안에 있는지 확인(점과 원 충돌)
////    vector<2> const distance = { LHS.Location[0] - RHS.Location[0], LHS.Location[1] - RHS.Location[1] };
////
////    if (distance[1] > ((RHS.Length[0] / 2) + (LHS.Diameter / 2))) { return false; }
////    if (distance[2] > ((RHS.Length[1] / 2) + (LHS.Diameter / 2))) { return false; }
////
////    if (distance[1] <= ((RHS.Length[0] / 2) + (LHS.Diameter / 2))) { return true; }
////    if (distance[2] <= ((RHS.Length[1] / 2) + (LHS.Diameter / 2))) { return true; }
////
////    //????.... ㅜㅜ
////    //vector<2> const min = { RHS.Location[0] - (RHS.Length[0] / 2) - (LHS.Diameter / 2), RHS.Location[1] - (RHS.Length[1] / 2) - (LHS.Diameter / 2) };
////    //vector<2> const max = { RHS.Location[0] + (RHS.Length[0] / 2) + (LHS.Diameter / 2), RHS.Location[1] + (RHS.Length[1] / 2) + (LHS.Diameter / 2) };
////
////    //여기서 부터 잘 모르겠습니다.... ㅜㅜ
////
////}
//
//bool Collide(Rectangle const& LHS, Rectangle const& RHS)
//{
//    //중점간의 벡터 구하기 위해 각각의 빼주기
//    vector<2> const distance = LHS.Location - RHS.Location;		//LHS 좌변 , RHS 우변
//
//    //distance[0]은 x 성분, [1]은 y성분
//
//    float constexpr radian = 3.141592653f / 180.0f;
//
//    //각 방향 벡터 구하기, axis의 복수(축이라는 뜻)
//    vector<2> const axes[4]
//    {
//        { cos(LHS.Angle * radian), sin(LHS.Angle * radian)},
//        {-sin(LHS.Angle * radian), cos(LHS.Angle * radian)},
//        { cos(RHS.Angle * radian), sin(RHS.Angle * radian)},
//        {-sin(RHS.Angle * radian), cos(RHS.Angle * radian)}
//    };
//
//    //vector<2>는 float 성분 2개를 가진 배열과 같다고 생각하면 됨.
//    vector<2> const vectors[4]
//    {
//        //LHS.Length[0] -> x 성분, LHS.Length[1] -> y 성분
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
//        //모든 벡터에 대한 사영을 더해줌
//        for (int j = 0; j < 4; ++j)
//            sum += abs(dot(axes[i], vectors[j]));
//
//        //현재 축의 중점간 거리의 절대값
//        if (sum < abs(dot(axes[i], distance)))
//            return false;
//    }
//
//    return true;
//}  
#pragma endregion
bool Collide(Point const& LHS, Circle const& RHS)
{
    // 점의 중점과 원의 중점 사이의 거리가 원의 반지름보다 작거나 같을때 충돌
    return length(LHS.Location - RHS.Location) <= RHS.Diameter / 2;
}


// 점과 사각형 충돌검사
bool Collide(Point const& LHS, Rectangle const& RHS)
{
    vector<2> const point[5]
    {
        {RHS.Location[0] - RHS.Length[0] / 2 , RHS.Location[1] - RHS.Length[1] / 2}, // point[0] -> x : min,  y : min
        {RHS.Location[0] - RHS.Length[0] / 2 , RHS.Location[1] + RHS.Length[1] / 2}, // point[1] -> x : min,  y : max
        {RHS.Location[0] + RHS.Length[0] / 2 , RHS.Location[1] - RHS.Length[1] / 2}, // point[2] -> x : max, y : min
        {RHS.Location[0] + RHS.Length[0] / 2 , RHS.Location[1] + RHS.Length[1] / 2}, // point[3] -> x : max, y : max
        {LHS.Location[0]								 , LHS.Location[1]							     }  // point[4] -> Point(x,y)
    };
    // 실질적으로 axes[1] 과 axes[2]은 필요가 없음

    if (point[4][0] >= point[0][0] && point[4][1] >= point[0][1] && point[4][0] <= point[3][0] && point[4][1] <= point[3][1])
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 원과 원 충돌검사
bool Collide(Circle const& LHS, Circle const& RHS)
{
    return length(LHS.Location - RHS.Location) <= LHS.Diameter / 2 + RHS.Diameter / 2;

    /* 원과 원 사이의 충돌 검사
        circle1의 반지름 : Diameter/2 = r1,  circle2의 반지름 : Diameter/2 = r2
        circle1과 circle 두 원 중점 사이의 거리 : length
        lengh = circle1의 Location< , >에서 circle2의 Location < , >의 거리를 빼주면 length
        sqrt((x1 - x2)^2) + ((y1- y2)^2) = length ^2
    */
}

// 원과 사각형 충돌검사
bool Collide(Circle const& LHS, Rectangle const& RHS)
{
    vector<2> const point[5]
    {
        {RHS.Location[0] - RHS.Length[0] / 2 , RHS.Location[1] - RHS.Length[1] / 2},  // point[0] -> x : min,  y : min
        {RHS.Location[0] + RHS.Length[0] / 2 , RHS.Location[1] + RHS.Length[1] / 2},  // point[1] -> x : max, y : max
        {LHS.Location[0] , LHS.Location[1]},  // point[2] -> Circle(x,y)
        {RHS.Location[0] - RHS.Length[0] / 2 , RHS.Location[1] + RHS.Length[1] / 2},   // point[3] -> x : min,  y : max
        {RHS.Location[0] + RHS.Length[0] / 2 , RHS.Location[1] - RHS.Length[1] / 2}    // point[4] -> x : max, y : min
    };

    if (point[0][0] <= point[2][0] && point[2][0] <= point[1][0]) // 사각형 x min < = 원의 x좌표 && 원의 x좌표<= 사각형 x의 max
    {
        if (point[2][1] + LHS.Diameter / 2 >= point[0][1] && point[2][1] <= point[1][1] + LHS.Diameter / 2) // 원의 y좌표에 + 원의 반지름 >= 사각형 y min && 원의 y좌표 <= 사각형 y의 max + 원의 반지름
            return true;
    }
    else if (point[0][1] <= point[2][1] && point[2][1] <= point[1][1]) // 사각형 y min <= 원의 y 좌표 && 원의 y좌표 <= 사각형 y max
    {
        if (point[2][0] + LHS.Diameter / 2 >= point[0][0] && point[2][0] <= point[1][0] + LHS.Diameter / 2) // 원의 x 좌표 + 원의 반지름 >= 사각형 x min && 원의 x 좌표 <= 사각형 y의 max + 원의 반지름
            return true;
    }
    else if (length(point[0] - LHS.Location) <= LHS.Diameter / 2)
        return true;
    else if (length(point[1] - LHS.Location) <= LHS.Diameter / 2)
        return true;
    else if (length(point[3] - LHS.Location) <= LHS.Diameter / 2)
        return true;
    else if (length(point[4] - LHS.Location) <= LHS.Diameter / 2)
        return true;

    //	// 점과 원 충돌검사
    //	bool Collide(Point const& LHS, Circle const& RHS)
    //{
    //	// 점의 중점과 원의 중점 사이의 거리가 원의 반지름보다 작거나 같을때 충돌
    //	return length(LHS.Location - RHS.Location) <= RHS.Diameter / 2;
    //}
}
bool Collide(Rectangle const& LHS, Rectangle const& RHS)
{
    //float v[2];
    //v[0] = 1;
    //v[1] = 2;

    vector<2> const distance = LHS.Location - RHS.Location;

    float constexpr radian = 3.141592653f / 180.0f;

    vector<2> const axes[4]			// axis 의 복수형
    {
        { cos(LHS.Angle * radian),		sin(LHS.Angle * radian) },
        { -sin(LHS.Angle * radian),		cos(LHS.Angle * radian) },
        { cos(RHS.Angle * radian),		sin(RHS.Angle * radian) },
        { -sin(RHS.Angle * radian),		cos(RHS.Angle * radian) }
    };

    vector<2> const vectors[4]
    {
        axes[0] * (LHS.Length[0] / 2),
        axes[1] * (LHS.Length[1] / 2),
        axes[2] * (RHS.Length[0] / 2),
        axes[3] * (RHS.Length[1] / 2),
    };

    for (int i = 0; i < 4; ++i)
    {
        float sum = 0;

        for (int j = 0; j < 4; ++j)
            sum += abs(dot(axes[i], vectors[j]));

        if (sum < abs(dot(axes[i], distance)))
            return false;
    }
    return true;
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
                    //if(Collide(dest_circle,circle)) //원 - 원
                    //if (Collide(dest_rect, circle)) // 사각 - 원
                    //{
                    //    shape_pos[i][0] = 1;
                    //    return true;
                    //}
                    break;
                }
                case rect:
                {
                    Rectangle rect;
                    rect.Location = { shape_pos[i][2],shape_pos[i][3] };
                    rect.Angle = 0;
                    rect.Length = { shape_pos[i][4]*2,shape_pos[i][5]*2 };
                    //return Collide(dest_rect, rect);
                    //if(Collide(dest_point,rect)) //점 - 사각
                    //if(Collide(rect,dest_circle)) //원 - 사각
                    if (Collide(dest_rect, rect)) //사각 - 사각
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
