//
// 
// 점과 원  
// 두점 사이의 거리가 반지름 이하인경우 충돌
// 
// 점과 사각형
// 점이 min max 범위 안에 있을때
// 
// 원과 원
// 중점간의 거리가 두원 반지름
// 
// 원과 사각형
// 원의 중점이 너비와 높이 범위안에 원의 중점이 걸린경우
// 원의 r만큼 확장한 사각형과 원의 중점과의 충돌비교를 시행
// 이후 원의 중점이 사각형의 중점과 비교하여 
// 각 사분면의 꼭지점과 원과의 충돌비교를 시행
// 
// 
// 회전 변환 행렬
// cos    -sin
// sin    cos
// 
// 0
// 1    0
// 0    1
// 
// 90
// 0    -1
// 1    0
// 
// 180
// 1    0    
// 0    1
// 
// 
// 
//
