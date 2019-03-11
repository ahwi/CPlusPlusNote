## 14.8 函数调用运算符



### 14.8.1 lambda是函数对象

**当我们编写一个lambda后，编译器将该表达式翻译成一个未命名的命名对象**

例子：

```c++
//根据单词的长度对其进行排序
stable_sort(words.begin(), words.end(), 
            [](const string &a, const string &b)
            {return a.size() < b.size();});

//其行为类似与下面这个类的一个未命名对象
class ShortString{
public:
    bool operator()(const string &s1, const string &s2) const{
        return s1.size() < s2.size();
    }
};

```



**表示lambda及相应捕获行为的类：**

* 当一个lambda表达式通过引用捕获变量时，编译器可以直接使用该引用而无须再lambda产生的类中将其存储为数据成员。

* 通过值捕获的变量被拷贝到lambda中时，lambda产生的类必须为每个值捕获的变量建立对应的数据成员，同时创建构造函数。

* 例子：

  ```c++
  
  //获得第一个指向满足条件元素的迭代器，该元素满足size() is >= sz
  auto wc = find_if(worlds.begin(), words.end(), 
                   [sz](const string &a)
                    {return a.size() >= sz;});
  
  //该lambda表达式产生的类将形如：
  class SizeComp{
  	SizeComp(size_t n):sz(n){}	//该形参对应捕获的变量  
    	//该调用运算符的返回类型、形参和函数体都与lambda一致
      bool operator()(const string &s) const
      {return s.size() > sz;}
  private:
      size_t sz;	//该数据成员对应通过只获取的变量
  };
  ```


### 14.8.2 标准库定义的函数对象

标准库定义了一组表示算术运算符、关系运算符和逻辑运算符的类

**在算法中使用标准库函数对象：**

表示运算符的函数对象长用来替代算法中的默认运算符

需要特别注意的时，标准库规定其函数对象对于指针同样适用



### 14.8.3 可调用对象与function

c++语言中有几种可调用的对象：<font color=red>函数</font>、<font color=red>函数指针</font>、<font color=red>lambda表达式</font>、<font color=red>bind创建的对象</font>

**可调用的对象也有类型：**

* 每个lambda有它自己唯一的（未命名）类类型；
* 函数及函数指针的类类型则由其返回值类型和实参类型决定，等等

**调用形式：**指明了调用返回的类型以及传递给调用的实参类型。一种函数形式对应一个函数类型（注意函数类型和可调用对象类型不是一个概念），例如：

​	int (int, int)

是一个函数类型，它接受两个int、返回一个int



**不同类型可能具有相同的调用形式：**

对于几个可调用对象共享同一种对用形式的情况，有时<font color=red>希望把它们看成具有相同的类型</font>。

如：

```c++
//普通函数
int add(int i, int j) { return i + j; }
//lambda,其产生一个未命名的函数对象类
auto mod = [](int i, int j){return i % j;};
//函数对象类
struct divide {
    int operator(int denominator, int divisor){
        return denominator / devicsor;
    }   
}
```

<font color=red>尽管上面的可调用对象类型各不相同，但是共享同一种调用形式：</font>

int (int, int);

为了实现这一目的，需要定义一个**函数表**用于存储指向这些可调用对象的“指针”，当程序需要指向某个特定操作时，从表中查找该调用函数，如下：

```c++
//构建从运算符到函数指针的映射关系，其中函数接受两个int、返回一个int
map<string, int(*)(int, int)> binops;
```

我们可以按照下面的形式将add的指针添加到binops中：

```c++
//正确:add是一个指向正确类型函数的指针
binops.insert({"+", add}); //{"+", add}是一个pair
```

但是不能将mod或者divide存入binops中(问题在于mod是个lambda表达式，而每个lambda有它自己的类类型，该类型与存储在binops中的值的类型不匹配):

```c++
binops.insert({"%", mod}); //错误：mod不是一个函数指针
```



**标准库function类型：**

为了解决上述问题，我们可以使用一个名未**function**的新的标准库类型解决上述问题。(function定义在functional头文件中，标14.3列举了function定义的操作，详情可见p512)

<font color=red>function是一个模板</font>

我们可以使用如下方式，表示任何一种可调用对象类型：

```c++
function<int(int, int)>
function<int(int, int)> f1 = add;		//函数指针
function<int(int, int)> f2 = divide();	//函数对象类的对象
function<int(int, int)> f3 = [](int i, int j){//lambda
							return i * j;
}

cout << f1(4,2) << endl;
cout << f2(4,2) << endl;
cout << f3(4,2) << endl;
```

因此我们可以使用下面的形式重新定义map，解决上述问题：

```c++
map<string, function<int(int, int)>> binops;

map<string, functin<int(int, int)>> binops = {
    {"+", add},									//函数指针
    {"-", std::minus<int>{}},					//标准库函数对象
    {"/", divide()},							//用户定义的函数对象
    {"*", [](int i, int j){ return i * j;}},	//未命名的lambda
    {"%", mod}									//名了名的lambda对象
}

//调用
binops["+"](10,5);	//调用add(10,5)
binops["-"](10,5);	//调用minus<int>对象的调用运算符
...
```

**重载的函数与function:**

我们<font color=red>不能(直接)将重载函数的名字存入function类型的对象中</font>，会产生二义性,比如:

```c++
int add(int i, int j){return i + j;}
Sales_data add(const Sales_data&, const Sales_data &);
map<string, function<int(int, int)>> binops;
binops.insert( {"+", add} );	//错误：哪个add?
```

解决上述二义性问题，有两条途径：

* 存储函数指针而非函数的名字：

  ```c++
  int (*fp)(int,int) = add;		//指针所指的add是接受两个int的版本
  binops.insert({"+", fp});		//正确：fp指向一个正确的add版本
  ```

  ​			

* 使用lambda来消除二义性：

  ```c++
  //正确：使用lambda来指定我们希望使用的add版本
  binops.insert({"+", [](int a, int b){return add(a, b);}});
  ```



## 14.9 重载、类型转换与运算符

**类类型转换（class-type conversions）：**<font color=red>转换构造函数</font>和<font color=red>类型转换运算符</font>共同定义了类类型转换（class-type conversions），这样的转换有时也被称作**用户定义的类型转换(user-defined conversions)**

### 14.9.1 类型转换运算符

**类类型转换运算符(conversion operator)：**是类的一种特殊成员函数，它负责将一个类类型的值转换成其他类型。

  类型转换函数的一般形式如下所示：

  ````c++
operator type() const;

//其中type表示某种类型
  ````

<font color=red>注：</font>

* 类型转换运算符可以面向任意类型（处理void之外）进行定义，只要该类型能作为函数的返回类型。因此，我们不允许转换成数组或者函数类型，但允许转换成指针（包括数组指针及函数指针）或者引用类型。
* 一个类型转换函数必须是类的成员函数：它不能是声明返回类型，形参列表也必须为空。类型转换函数通常应该是const。

#### 定义含有类型转换运算符的类：

例子：

​	定义一个类，令其表示0到255之间的一个整数：

```c++
class SmallInt{
public:
    SmallInt(int i = 0):val(i){
        if(i < 0 || i > 255)
            throw std::out_of_range("Bad SmallInt value");
    }
    operator int() const { return val; }
private:
    std::size_t val;
};
```

SmallInt类既定义了向类类型的转换（构造函数），也定义了从类类型向其他类型的转换（类型转换运算符）

```c++
si = 4;	//首先将4隐隐式地转化成SmallInt,然后调用SmallInt::operator=
si + 3;	//首先将si隐式地转成int，然后指向整数的加法
```

因为类型转换运算符是隐式执行的，所以无法给这些函数传递实参，当然也就不能再类型转换运算符的定义中使用任何形参。同时，景观类型转换函数不负责指定返回类型，但实际上每个类型转换函数都会返回一个对应类型的值：

```c++
class SmallInt;
operator int(SmallInt&);		//错误：不是成员函数
class SmallInt{
    int operator int() const;		//错误：指定了返回类型
    operator int(int = 0) const;	//错误：参数列表不为空
    operator int*() const { return 42;}	//错误：42不是一个指针
};
```



#### 类型转换运算符可能产生意外结果：

如下：

```c++
int i = 42;
cin << i;	//如果向bool的类型转换不是显示的，则该代码再编译器看来将是合法的
```

<font color=red>说明：</font>这段代码试图将输出运算符作用于输入流。因为istream本身并没有定义<<，所以本来代码应该产生错误。然而，该代码能使用istream的bool类型转换运算符将cin转换成bool，而这个bool值接着会被提升成int并作内置的左移运算符的左侧运算对象。这样用来，提升后的bool值（0或1）最终会被左移42个位置。这一结果与我们预期大相径庭。



#### 显示的类型转换运算符：

为了防止上述的异常情况，c++11引入了显式的类型转换运算符（explicit conversion operator）:
  ```c++
  class SmallInt{
  public:
      //编译器不会自动执行这一类型转换
      explicit operator int() const{ return val;}
  	//其他成员与之前的版本一致    
  };
  ```


* 当类型转换运算符是显式的时候，必修通过显式的强制类型转换才可以：

  ```c++
  SmallInt si = 3;	//正确：Smaill的构造函数不是显式的
  si + 3;				//错误：此处需要隐式的类型转换，但类的运算符是显式的
  static_cast<int>(si) + 3;	//正确：显式地请求类型转换
  ```

* <font color=red>这一规定存在一个例外，即如果表达式被用作条件，则编译器 会将显式的类型转换自动应用与它。</font>当表达式出现在下列位置时，显式的类型转换将被隐式地执行：
  * if、while及do语句的条件部分
  * for语句的条件表达式
  * 逻辑非运算符(!)、逻辑或运算符(||)、逻辑与运算符(&&)的运算对象
  * 条件运算符（?:）的条件表达式



#### 转换为bool：

**在c++11新标准下，IO标准库通过定义一个向bool的显式类型转换，避免上述提到的问题：**

<font color=red>无论我们说明时候在条件中是用哪个流对象，都会使用为IO类型定义的operator bool。</font>

例如：

```c++
while(std::cin >> value)
```

解释：while语句的条件执行了输入运算符，它负责将数据读入到value并返回cin。为了对条件求值，cin被istream operator bool类型转换函数隐式地执行了转换（cin被专程了bool类型）。

