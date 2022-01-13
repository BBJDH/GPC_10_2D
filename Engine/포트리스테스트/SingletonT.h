#pragma once
template <typename T>
class SingletonT
{
protected:
	//싱글톤 인스턴스 선언
	//static으로 한번만 생성되도록 작성
	static T * singleton_instance;
	SingletonT() {};
	~SingletonT() {};

public:
	//생성된 인스턴스 반환
	static T* get_singleton();
	//생성된 인스턴스 메모리에서 해제
	void release_singleton();

};

//정의

//인스턴스 선언
template<typename T>
T* SingletonT<T>::singleton_instance = nullptr;

//싱글톤 인스턴스 반환
template<typename T>
T* SingletonT<T>::get_singleton()
{
	if (singleton_instance == nullptr)
		singleton_instance = new T;
	return singleton_instance;
}
//생성된 인스턴스 메모리에서 해제
template<typename T>
void SingletonT<T>::release_singleton()
{
	if (singleton_instance != nullptr)
	{
		delete singleton_instance;
		singleton_instance = nullptr;
	}
}