#include <iostream>


#if 0 //v1
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

	void PrintName()
	{
		m_Name.Print();
	}
private:
	String m_Name;
};


int main() 
{
	// "Cherno" ��ʽת���� String���ȼ��ڣ� Entity entity(String("Cherno"));
	Entity entity("Cherno");
	entity.PrintName();

	std::cin.get();
	return 0;
}

#endif


#if 1 // v2 �����ƶ�����
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
		//: m_Name(name) // �÷�ʽ����ʹ��Sting�Ŀ������췽��
		//: m_Name((String&&) name) // �÷�ʽ�����String���ƶ����캯��
		: m_Name(std::move(name)) // �÷�ʽҲ�����String���ƶ����캯����ֻ�Ǳ�����Ĺ淶
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
	// "Cherno" ��ʽת���� String���ȼ��ڣ� Entity entity(String("Cherno"));
	Entity entity("Cherno");
	entity.PrintName();

	std::cin.get();
	return 0;
}


#endif