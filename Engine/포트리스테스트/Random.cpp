#include "Random.h"
#include "stdafx.h"


#pragma region Random 클래스 정의
//중복 없는 랜덤 실행
// 시작 수 ~ 끝수 범위 지정(-정수도 가능, 사이즈는 unsigned int),
// 총 몇개를 추출, 배열로 차례대로 넣어서 반환(동적할당된 배열의 포인터로 반환)
// ex) 1~ 50 까지
//-> 동적할당으로 size 50, 초기화는 1~50, 인덱스 랜덤
//index = rand()%size 로 받아 뽑힌 랜덤 인덱스의 값은 뽑힌 결과 어레이에 넣고,
//index의 값과 배열의 제일 끝(size-1)값과 교체 후 size 1 감소 
// ->다음 rand()%size 에서 size가 1감소했으므로 맨 끝 배열의 값은 rand에서 제외된다
//[12345] 에서 3이 뽑히면 [1254]3  ([]가 rand의 범위, 뽑을때마다 --size;)


// 1 2 3 4 5 6 7 8 9
// 0 1 2 3 4 5 6 7 8  rand()%9 ->0~8
// 5가 선출
// 1 2 3 4 5 9 7 8] 6
// rand()%8 
//
Random::Random(int const& start_num, int const& end_num, unsigned const& count) :arr_size(count)
{
	assert(end_num > start_num);
	assert(count > 0);

	unsigned size = end_num - start_num + 1;
	int value = start_num;

	int* const Arry_Range = new int[size] {};

	for (unsigned i = 0; i < size; ++i)
	{
		Arry_Range[i] = value++;
	}  //범위 지정

	result = new int[count] {};


	for (unsigned i = 0; i < count; ++i)
	{
		int const index = rand() % size;
		result[i] = Arry_Range[index];
		Swap(Arry_Range[index], Arry_Range[size - 1]);
		--size;
	}

}
Random::Random(Random const& r) :result(r.result), arr_size(r.arr_size)
{}
int Random::GetResult(unsigned const& index)const
{
	assert(index < arr_size);
	return result[index];
}
bool Random::operator==(Random const& right_rand)const
{
	
	return this->result == right_rand.result;
}
bool Random::operator!=(Random const& right_rand)const
{
	return !(*this==right_rand);
}
//void Random::Print() const
//{
//	for (unsigned i = 0; i < arr_size; i++)
//	{
//		std::cout << result[i] << "\t";
//		if (i % 10 == 9)
//			std::cout << std::endl;
//	}
//	std::cout << std::endl;
//
//}

Random::operator int() const
{
	assert(result != nullptr);
	assert(arr_size == 1);
	return result[0];
}

Random& Random::operator=(Random const& right_rand)
{
	if (*this != right_rand)
	{
		delete[] result;
		this->arr_size = right_rand.arr_size;
		this->result = new int[this->arr_size];
		for (size_t i = 0; i < right_rand.arr_size; i++)
		{
			this->result[i] = right_rand.result[i];
		}
	}
	return *this;

}

Random::~Random()
{
	delete[] result;
}

constexpr void Random::Swap(int& a, int& b)
{
	int temp = 0;
	temp = a;
	a = b;
	b = temp;
}

#pragma endregion