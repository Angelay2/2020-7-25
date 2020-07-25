#include <iostream>
using namespace std;
//RAII思想：根据对象的生命周期控制资源的生命周期
//RAII一个应用： 智能指针 -->根据智能指针对象的生命周期控制动态开辟的资源的生命周期
template <class T>
struct smartPtr
{
public:
	smartPtr(T* ptr)
		:_ptr(ptr)
	{}

	~smartPtr()
	{
		cout << "~smartPtr : delete" << endl;
		delete[] _ptr;
	}
private:
	T* _ptr;
};

void testSP()
{
	while (1)
	{
		int* ptr = new int[100];
		//smartPtr<int> sp(ptr);

		throw 1;
		/*cout << "delete" << endl;
		delete[] ptr;*/
	}
}

void testSP2()
{
	//int num = 1000;
	while (1)
	{
		try
		{
			testSP();
		}
		catch (int a)
		{

		}
	}
}

int main()
{
	//testSP();
	testSP2();
	return 0;
}