#include <thread>
#include <iostream>
#include <atomic>
#include <mutex>
using namespace std;
/*
1. 多线程安全
1. 原子操作: 指令不会被打断, 线程安全的操作, 效率高
automic<T>: 把T类型数据封装成原子操作
2. 加锁: 通过多线程之间加锁阻塞, 保证线程安全, 效率较低, 加锁解锁比较耗时(相比于原子操作)
mutex, recrusive_mutex, timed_mutex, recrusive_timed_mutex
lock: 阻塞式解锁
unlock: 解锁
try_lock: 非阻塞式加锁
lock_guard, unique_lock: RAII 实现
通过对象的生命周期控制锁的生命周期
构造函数: 加锁
析构函数: 解锁
防拷贝: 本身不支持拷贝,;
*/

//unsigned long sum = 0L;
atomic<int> sum(0);

struct number
{
	int _num = 0;
	number& operator++()
	{
		++_num;
		return *this;
	}
};

number n;
atomic<number> atomic_number(n);


void fun(size_t num)
{
	for (size_t i = 0; i < num; ++i)
		sum++;
}

void fun2(size_t num)
{
	for (int i = 0; i < num; ++i)
		++n;
}


void testThread()
{
	int num;
	cin >> num;

	thread t1(fun, num);
	thread t2(fun, num);

	t1.join();
	t2.join();

	cout << sum << endl;

	//atomic:防拷贝
	/*atomic<int> sum2 = sum;
	atomic<int> copy(sum);*/
}


void testThread2()
{
	int num;
	cin >> num;

	thread t1(fun2, num);
	thread t2(fun2, num);

	t1.join();
	t2.join();

	cout << n._num << endl;
}

mutex mtx;
int global = 0;
void fun3(int num)
{
	for (int i = 0; i < num; ++i)
	{
		//mtx.try_lock: 非阻塞加锁操作：如果其它线程没有释放当前的锁，则直接返回加锁失败的结果
		//mtx.lock:  阻塞加锁操作：如果其它线程没有释放当前的锁，阻塞等待，直到其它线程释放当前锁
		mtx.lock();
		//如果当前线程拥有该锁，执行第二次的加锁操作，会导致死锁
		//mtx.lock();
		++global;
		mtx.unlock();
	}

}

void testThread3()
{
	int num;
	cin >> num;

	thread t1(fun3, num);
	thread t2(fun3, num);

	t1.join();
	t2.join();

	cout << global << endl;
}

//守卫锁
template <class Mutex>
class lockGuard
{
public:
	//构造函数加锁
	lockGuard(Mutex& mtx)
		:_mtx(mtx)
	{
		//cout << "lockGuard(Mutex&)" << endl;
		_mtx.lock();
	}

	//析构函数解锁
	~lockGuard()
	{
		//cout << "~lockGuard" << endl;
		_mtx.unlock();
	}

	//防拷贝
	lockGuard(const lockGuard<Mutex>&) = delete;
	lockGuard& operator=(const lockGuard<Mutex>&) = delete;
private:
	Mutex& _mtx;
};

void fun4(int num)
{
	for (int i = 0; i < num; ++i)
	{
		//创建守卫锁
		lockGuard<mutex> lg(mtx);
		//防拷贝
		//lockGuard<mutex> copy(lg);
		++global;
	}

}

void testThread4()
{
	int num;
	cin >> num;

	thread t1(fun4, num);
	thread t2(fun4, num);

	t1.join();
	t2.join();

	cout << global << endl;
}

//int main()
//{
//	//testThread();
//	//testThread2();
//	//testThread3();
//	testThread4();
//	return 0;
//}