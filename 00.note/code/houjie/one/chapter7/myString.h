#ifndef __myString__
#define __myString__

class String
{
public:
    String(const char* cstr = 0);
    // 拷贝构造函数
    String(const String& str);
    // 拷贝赋值函数
    String& operator=(const String& str);
    // 析构函数
    ~String();
    char * get_c_str() const {return m_data;};
private:
    char * m_data;
};


#endif