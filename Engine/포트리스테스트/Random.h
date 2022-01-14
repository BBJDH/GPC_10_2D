#pragma once

//중복 없는 랜덤 실행
// 시작 수 ~ 끝수 범위 지정(-정수도 가능, 사이즈는 unsigned int),
// 총 몇개를 추출, 배열로 차례대로 넣어서 반환(동적할당된 배열의 포인터로 반환)
// ex) 1~ 50 까지
//-> 동적할당으로 size 50, 초기화는 1~50, 인덱스 랜덤
//index = rand()%size 로 받아 뽑힌 랜덤 인덱스의 값은 뽑힌 결과 어레이에 넣고,
//index의 값과 배열의 제일 끝(size-1)값과 교체 후 size 1 감소 
// ->다음 rand()%size 에서 size가 1감소했으므로 맨 끝 배열의 값은 rand에서 제외된다
//[12345] 에서 3이 뽑히면 [1254]3  ([]가 rand의 범위, 뽑을때마다 --size;)
class Random 
{
private:
	constexpr void Swap(int& a, int& b);
	int* result;
	unsigned int arr_size;

public:

	Random() = default;
	Random(int const& start_num, int const& end_num, unsigned const& count);
	Random(Random const& r);
	int GetResult(unsigned const& index)const;
	bool operator ==(Random const & right_rand)const;
	bool operator !=(Random const & right_rand)const;
	Random& operator =(Random const & right_rand);
	operator int() const; //rand를 단일 정수로 반환 취급하는경우
	~Random();

	//void Print()const; //콘솔 테스트용

};