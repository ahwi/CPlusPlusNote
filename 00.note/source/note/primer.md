# 资料：

示例程序：http://www.informit.com/title/0321714113



# 第2章 变量和基本类型

## 2.1 基本内战类型

**基本数据类型：**

* 算术类型
  * 字符
  * 整型数
  * 布尔值
  * 浮点数
* 空类型

**内置类型的机器实现：**

大多数计算机以2的整数次幂个比特作为块来处理内存，可寻找的最小内存块称为“字节（byte）”，存储的基本单元称为“字（word）”，它通常由几个字节组成

**关于char的使用建议：**

在算术表达式中不要使用char或bool，只有在存放字符或布尔值时才使用它们。因为类型char在一些机器上是有符号的，而在另一些机器上又是无符号的，所以如果使用char进行运算特别容易出问题。

# 第7章 类

类的基本思想：

* 数据抽象(data abstraction)：一种依赖于接口和实现分离的编程（以及设计）技术
* 封装(encapsulation)：实现了类的接口和实现的分离。

## 7.1 定义抽象数据类型

### 7.1.1 设计`Sales_data`类

`Sales_data`的接口应该包含的操作：

* `isbn` 成员函数，用于返回对象的ISBN编号。
* `combine` 成员函数，用于将一个`Sales_data`对象加到另一个对象上。
* `add` 函数，执行两个`Sales_data`对象的加法。
* `read`函数，将数据从`istream`读入到`Sales_data`对象中。
* `print` 函数，将`Sales_data`对象的值输出到ostream。

成员函数（非接口部分）：

* `avg_price` 返回售出书籍的平均价格

数据成员：

* `bookNo` string类型，表示ISBN编号
* `units_sold` unsigned 类型，表示某本书的销量
* `revenue` double 类型，表示这本书的总销量收入

**使用`Sales_data`**类

使用`Sales_data`类读取数据：

```txt
0-201-70353-X 4 24.99
0-201-82470-1 4 45.39
0-201-88954-4 2 15.00 
0-201-88954-4 5 12.00 
0-201-88954-4 7 12.00 
0-201-88954-4 2 12.00 
0-399-82477-1 2 45.39
0-399-82477-1 3 45.39
0-201-78345-X 3 20.00
0-201-78345-X 2 25.00
```

代码：

作用：一行一行读取上面的数据，相同的ISBN编号进行累加，然后打印

```c++
Sales_data total;				//保存当前求和结果的变量
if(read(cin, total)){			//读入第一笔交易
    Sales_data trans;			//保存下一条交易数据的变量
    while(read(cin, trans)) {	//读入剩余的交易
        if(total.isbn() == trans.isbn())	//检查isbn
            total.combine(trans);			//更新变量total当前的值
        else {
            print(cout, total) << endl;		//输出结果
            total = trans;					//处理下一本书
        }
    }
    print(cout, total) << endl;			//输出最后一笔交易
} else {									//没用输入任何信息
    cerr << "No data?!" << endl;			//通知用户
}
```

**定义`Sales_data`类**

```c++
struct Sales_data {
    // 新成员：关于Sales_data对象的操作
    std::string isbn() const {return bookNo;}
    Sales_data& combine(const Sales_data&);
    double avg_price() const;
    //数据成员
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

//Sales_data 的非成员接口函数
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);
```

成员函数的声明必须在类的内部，它的定义则既可以在类的内部也可以在类的外部。

定义在类内部的函数是隐式的`inline`函数。

**this**

成员函数通过一个名为`this`的额外的隐式参数来访问调用它的那个对象。

如下：

```c++
total.isbn();
```

编译器负责把total的地址传递给isbn的隐式形参this，可以等价地任务编译器将该调用重写成了如下的形式：

```c++
// 伪代码，用于说明调用成员函数的实际执行过程
Sales_data::isbn(&total);
```

this 是隐式定义的，任何自定义名为 this 的参数或变量的行为都是非法的。

this 是一个常量指针，不允许改变 this 中保存的地址。

可以隐式的使用this调用类成员，也可以显示的调用：

```c++
std::string isbn() const {return bookNo;}
std::string isbn() const {return this->bookNo;}
```

**`const` 成员函数**

`isbn`函数参数列表后面有个`const`关键字，这里`const`的作用是修改隐式 this 指针的类型。

<font color=red>默认情况下，this 指向的是类类型非常量版本的常量指针。</font>

例如：

* 在`Sales_data`成员函数中，this 的类型是 `Sales_data *const`
* 默认情况下，不能把 this 绑定到一个常量对象上
* 不能在常量对象上调用一个普通函数（不然可能修改到对象）
* 如果成员函数不会修改对象内容，则可以声明成 `const` 类型，即把 this 声明成 `const Sales_data *const`类型。

**类作用域和成员函数**

* 类本身就是一个作用域

* 成员函数体可以随意使用类中的其他成员而无须在意这些成员的出现次序

> 编译器分两步处理类：首先编译成员的声明，然后才轮到成员函数体

**在类的外部定义成员函数**

```c++
double Sales_data::avg_price() const {
    if(units_sold)
        return revenue/units_sold;
    else
        return 0;
}
```

`Sales_data::avg_price`使用作用域运算符说明：定义了一个名为`avg_price`的函数，并且该函数被声明在`Sales_data`的作用域内。

**定义一个返回 this 对象的函数**

```c++
Sales_data& Sales_data::combine(const Sales_data &rhs)
{
    units_sold += rhs.units_sold;	//把 rhs 的成员加到this对象上
    revenue += rhs.revenue;
    return *this;					// 返回调用该函数的对象
}
```

**定义read和print函数**

```c++
// 输入的信息包括 ISBN、售出总数和售出价格
std::istream &read(std::istream &is, Sales_data &item)
{
    double price;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

std::ostream &print(std::ostream &os, const Sales_data &item)
{
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}
```

* IO类属于不能拷贝的类型，因此通过引用传递它们。
* 因为读取和写入操作会改变流的内容，所以两个函数接收的都是普通的引用，而非对常量的引用。

* `print`函数不负责换行，一般执行输出任务的函数应该减少对格式的控制，这样可以确保由用户代码来决定是否换行。

**定义add函数**

```c++
Sales_data add(const Sales_data &lhs,  const Sales_data &rhs)
{
    Sales_data sum = lhs;   //把 lhs 的数据成员拷贝给 sum
    sum.combine(rhs);       //把 rhs 的数据成员加到 sum 当中
    return sum;
}
```

### 7.1.4 构造函数

构造函数（constructor）：

* 构造函数的任务是初始化类对象的数据成员，无论何时只要类的对象被创建，就会执行构造函数

* 构造函数和类名相同，没有返回值，有一个（也可能为空）参数列表和一个（可能为空的）函数体

* 类可以包含多个构造函数，不同的构造函数之间必须在参数数量或参数类型上有所区别

* 构造函数不能被声明成`const`的

  > 当我们创建类的一个`const`对象时，直到构造函数完成初始化过程，对象才真正取得其"常量"属性。因此构造函数在`const`对象的构造过程中可以向其写值。





















































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



# 第12章 动态内存

* 静态内存
* 栈内存
* 自由空间(堆)

## 12.1 动态内存与智能指针

两种智能指针：

* <font color=red>shared_ptr</font>

  允许多个指针指向同一个对象

* <font color=red>unique_ptr</font>

  "独占"所指向的对象

* <font color=red>weak_ptr</font>

  伴随类，它是一种弱引用，指向shared_ptr所管理的对象

### 12.1.1 shared_ptr类





# 第15章 面向对象程序设计

## 15.6 继承中的类作呕能够与









# 第18章 用于大型程序的工具

 ## 18.3 多重继承与虚继承

**多重继承（multiple inheritance）：**是指从多个直接基类中产生派生类的能力。

### 18.3.1 多重继承

在派生类的派生列表中可用包含多个基类：

```c++
class Bear : public ZooAnimal{}
class Panda: public Bear, public Endangered {};
```

* 每个基类包含一个可选的访问说明符，如果访问说明符被忽略掉了，则关键字class对应的默认访问说明符是private，关键字struct对应的是public

* 对于派生类能够继承的基类个数，c++没有进行特殊规定

#### 多重继承的派生类从每个基类中继承状态

  ![图18-2](assets/图18-2-1552307078545.jpg)

  在Panda对象中含有一个Bear部分（其中又含有一个ZooAnimal部分）、一个Endangered部分以及在Panda中声明的非静态数据成员

#### 派生类构造函数初始化所有基类

基类的构造顺序与派生类列表中基类的出现顺序保持一致，而与派生类构造函数初始值列表中基类的顺序无关。

#### 继承的构造函数与多重继承

在c++11新标准中，允许派生类从它的一个或几个基类中继承构造函数，但是如果从多个基类中继承了相同的构造函数（即形参列表完全相同），则程序将产生错误：

```c++
struct Base1{
    Base1() = default;
    Base1(const std::string&);
    Base1(std::shared_ptr<int>);
};

struct Base2{
    Base2() = default;
    Base2(const std::string&);
    Base2(int);
};

//错误：D1试图从两个基类中都继承D1:D1(const string&)
struct D1: public Base1， public Base2{
    using Base1::Base1;	//从Base1继承构造函数
    using Base2::Base2;	//从Base2继承构造函数
};
```

如果一个类从它的多个基类中继承了相同的构造函数，则这个类必修为该构造函数定义它自己的版本：

```c++
struct D2: public Base1, public Base2{
    using Base1::Base1;	//从Base1继承构造函数
    using Base2::Base2;	//从Base2继承构造函数
    //D2必须自定义一个接受string的构造函数
    D2(const string &s):Base1(s), Base2(s){}
    D2() = default;	//一旦D2定义了它自己的构造函数，则必须出现
};
```



#### 多重继承的派生类的拷贝与移动操作

* 与只有一个基类的继承一样，多重继承的派生类如果定义了自己的拷贝/赋值构造函数和赋值运算符，则必须在完整的对象上执行拷贝、移动或赋值操作
* 只有当派生类使用的是合成版本的拷贝、移动或赋值成员时，才会自动对其基类部分执行这些操作





