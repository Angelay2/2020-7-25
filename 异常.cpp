#include <vector>
#include <iostream>
using namespace std;
int func()
{
	//return 1;
	try
	{
		//抛出异常
		throw 0;
	}
	catch (char n)
	{
		cout << "func catch(int)" << endl;
	}
	cout << "func" << endl;
	return 1;
}

void testE1()
{
	try
	{
		//try: 可能发生异常的代码，写在try代码块中
		func();
	}
	//catch捕获对应类型的异常
	catch (char ch)
	{
		cout << "catch(char)" << endl;
	}
	catch (char* str)
	{
		cout << "catch(char*)" << endl;
	}
	catch (float n)
	{
		cout << "testE1 catch (int)" << endl;
	}
	//catch(...): 放在整个catch代码块的最后，进行万能捕获
	catch (...)
	{
		cout << "catch(...)" << endl;
		//异常的重新抛出
		throw;
	}
	cout << "TestE1" << endl;
}


void testE2()
{
	try
	{
		testE1();
	}
	catch (int n)
	{
		cout << "testE2 catch (int)" << endl;
	}
	cout << "testE2" << endl;
}

void testE3()
{
	int* ptr = new int[1000];
	try
	{
		func();
	}
	catch (char ch)
	{

	}
	catch (char* str)
	{
	}
	catch (...)
	{
		//重新抛出之前，完成必要的操作
		cout << "catch(...) delete" << endl;
		delete[] ptr;
		//异常的重新抛出
		throw;
	}

	cout << "testE3 delete" << endl;
	delete[] ptr;
}

void testE4()
{
	try
	{
		testE3();
	}
	catch (int a)
	{
		cout << "testE4 catch(int)" << endl;
	}
}

void testE5()
{
	try
	{
		vector<double> vec;
		//vec.at(10) = 2.0;
		//vec.resize(0x3fffffff);
		char* ptr = new char[0x7fffffff];
	}
	//用所有异常的根基类的引用或者指针进行捕获，可以匹配所有继承体系的所有类型
	//通过根基类虚函数重写，完成多态的逻辑，最终产生多态的行为，完成异常的精确处理
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "未知异常" << endl;
	}
}



//int main()
//{
//	//testE1();
//	//testE2();
//	//testE4();
//	testE5();
//	return 0;
//}