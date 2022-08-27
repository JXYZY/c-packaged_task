// packaged_task.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <future>

int get_int(int x)
{
	std::this_thread::sleep_for(std::chrono::seconds(5));
	return x * 3;
}

int main()
{
#if 1
	//构造函数
	std::packaged_task<int(int)> foo(get_int);
	std::future<int> fut = foo.get_future();
	std::future<int> futTest;
	/*std::thread t1(std::move(foo),2);
	t1.detach();*/
	foo(2);
	//其实future.get本身自带阻塞，会阻塞当前线程，所以前面用join和detach都无所谓
	//int value = fut.get();
	std::cout << "triple 2 is:" << fut.get() << std::endl;

	//reset 如果不进行reset的话那么不能够两次调用get_future
	foo.reset();
	futTest = foo.get_future();
	std::thread(std::move(foo), 99).detach();
	std::cout << "Thre triple of 99 is " << futTest.get() << ".\n";

#endif
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
