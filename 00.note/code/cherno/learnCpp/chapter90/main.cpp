#include <iostream>


class String 
{
public:
	String() = default;
	String(const char* string) 
	{
		printf("Created!\n");
		m_Size = strlen(string);
		m_Data = new char[m_Size];
		memcpy(m_Data, string, m_Size);
	}

	String(const String& other) 
	{
		printf("Copied!\n");
		m_Size = other.m_Size;
		m_Data = new char[m_Size];
		memcpy(m_Data, other.m_Data, m_Size);
	}

	String(String&& other) noexcept
	{
		printf("Moved!\n");
		m_Size = other.m_Size;
		m_Data = other.m_Data;

		other.m_Size = 0;
		other.m_Data = nullptr;
	}

	String& operator=(String&& other) noexcept
	{
		printf("Moved!\n");

		if (this != &other) {

			delete[] m_Data;

			m_Size = other.m_Size;
			m_Data = other.m_Data;

			other.m_Size = 0;
			other.m_Data = nullptr;
		}
		return *this;
	}

	~String()
	{
		printf("Destroyed!\n");
		delete m_Data;
	}

	void Print()
	{
		for (uint32_t i = 0; i < m_Size; i++) {
			printf("%c", m_Data[i]);
		}
		printf("\n");
	}

public:
	char* m_Data;
	uint32_t m_Size;
};


class Entity
{
public:
	Entity(const String& name) 
		: m_Name(name)
	{
	}

	Entity(String&& name) 
		//: m_Name(name) // 该方式还是使用Sting的拷贝构造方法
		//: m_Name((String&&) name) // 该方式会调用String的移动构造函数
		: m_Name(std::move(name)) // 该方式也会调用String的移动构造函数，只是比上面的规范
	{
	}

	void PrintName()
	{
		m_Name.Print();
	}
private:
	String m_Name;
};


int main() 
{
	#if 0 // part 1
	String string = "Hello";
	// String dest = string; // 复制字符串到新变量中，并非移动

	// String dest = (String &&)string;
	// String dest((String &&)string);
	// 上面两种方式并非最优雅且不一定对每种类型都适用的方法，因此可以使用一个灵活一些的函数，可以在编译时用auto找出输入的类型
	String dest(std::move(string));
	#endif

	String apple = "Apple";
	String dest;

	std::cout << "Apple: ";
	apple.Print();
	std::cout << "Dest: ";
	dest.Print();
	
	dest = std::move(apple);

	std::cout << "Apple: ";
	apple.Print();
	std::cout << "Dest: ";
	dest.Print();

	std::cin.get();
	return 0;
}
