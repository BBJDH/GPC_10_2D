#pragma once
#include"stdafx.h"



class Tank : public Object
{
public:
	enum class State
	{
		Nomal_right, Nomal_left, Fire_right, Fire_left, Stop_right, Stop_left, //...
	};

private:
	State		   state;
	unsigned	   hp;
	unsigned	   stamina;
	float		   fire_angle;
	float		   fire_velocity;


public:



	Tank(Position const& pos, unsigned const width, unsigned const height);
	unsigned const gethp() const;
	void take_damage(unsigned const damage);
	void input_key(WPARAM const wparam);
	void setstate(State const state);

	
};


/*
포트리스 충돌 판정

캐릭터클래스
{
	private:
	체력
	좌표(x,y)
	낙하속도
	(낙하판정시 9.8씩 증가)
	캐릭터 너비높이
	고유이동거리(1~2정도)
	캐릭터서있는각도

	public:
	체력,좌표,서있는각도 반환함수
	데미지함수(폭탄&)
	낙하판정함수 호출()
	-현재 낙하속도를 토대로 픽셀판정(낙하속도0이면, 즉 낙하중이아니면 판정하지않음)후 낙하위치에 이동함수 호출
	이동함수(이동할 좌표) -낙하판정함수 또는 이동계산함수에 의해 호출
	이동계산함수(좌우 이동방향)
	
                           -
		--> - (가능)   --> -(불가능) 해당각도로부터 1픽셀씩 기울기가능
           --			 --



}
미사일 클래스
{
	private:
	좌표
	폭발타입(원 타원 다단히트 프로토타입은 원으로구현)
	폭발 반경 너비높이
	데미지
	이동각도
	발사속도(발사 파워(힘)에따라, 중력가속도에 따라 변동)

	public:
	이동함수(이동할 좌표)
	이동계산함수()
	-다음 이동할 좌표를 계산, 충돌폭발이라면 폭발위치가 이동할 좌표이며 이동함수 호출 후 폭발함수를 호출
	폭발함수(캐릭터클래스 배열, 캐릭터수)
	-충돌한 캐릭터들의 데미지함수 호출, 낙하판정함수호출

}



폭발판정(폭탄의 중점,터뜨릴거리)
폭탄의 중점으로부터 터뜨릴거리에 있는 픽셀들(원형모양)과 픽셀 판정
맵픽셀이 확인되면 폭발하며
중점 이동시마다 호출


--폭발함수(, 캐릭터클래스 배열(사용할데이터 : 캐릭터위치,캐릭터너비높이),캐릭터수)--
중점으로부터 폭발반경만큼 검사(타원과 회전 사각형 충돌 판정)
폭발 반경 안에 있는 캐릭터들은 데미지 함수와 낙하 판정(픽셀판정)함수를 호출

--캐릭터.데미지 함수(폭탄&)--
폭발 중점으로부터의 거리에따라 데미지 부여(정수형 반환)

--낙하판정--
캐릭터의 밑에점 3개~5(일단 3개로)와
바로 밑에점 3개너비, 낙하가속도에따른 최대3X4까지 픽셀 충돌 검사
		---
		---
		---
		---
*/