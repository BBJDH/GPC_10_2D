#include<Windows.h>
#include<vector>


namespace Collision
{
	//충돌판정 로직
	//점대점
	//플레이어 - 미사일 간격이 15px 이하면 충돌
	bool const iscrash(std::vector<POINT> const& missile,
		POINT const & player)
	{
		return false;
	}

}