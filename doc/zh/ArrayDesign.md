# 关于Array类的设计

### 在编写Array类之前，我们有以下几个问题考虑
1.Array的实现是否应该与Matrix分开  
2.Array是否应该可以变化大小  
3.Matrix的维度是否应该当作类型的一部分  
4.Matrix是行优先还是列优先  

### 在几周的思考后我做出以下决定
1.Array类是一个既可以满足正常数组的功能需求，又能够当作高维数组使用的类  
2.Array大小可以变化  
3.Matrix的维度信息不应该当作类型的一部分  
4.列优先  


### 接下来，我会对以上几点做出解释
1.Array可以看作只有一个维度的矩阵，因此放在同一个类中表示是可行且正常的想法  
2.Array在进行cat等操作时会需要额外的空间，因此动态扩展空间的需求是存在的  
3.当维度信息作为类型的一部分时，函数接受参数时重载会比较麻烦，容易混乱  
例如，把Matrix这么写  
```cpp
template<class T>  
class Matrix  
{  
    private:  
    Array<Array<T> > data;  
    public:  
    ...other...  
};  
```

这样三维，四维的矩阵怎么表示？如何保证内层Array<T>长度相同？  

4.维度是很容易弄乱思维的的细节，画图会比较直观  
例如矩阵:  
1 2  
3 4  
5 6  
它3行2列  
如果是一个三维矩阵，可以写作：  
3,2,x  
如果是列优先，  
我们发现在表达的时候恰好从左到右维度升高，  
而行优先的话，  
第一二维会与表达方式相背。  
我们在书写上习惯于把行数（行优先的第二维，列优先第一维）写在前，列数（行优先的第一维，列优先第二维）写在后。  
为了表达方便，我采用了列优先。  
这也是我使用列优先的原因之一。  
  
其次，在读取音频文件到矩阵时，以列的方式显示会便于用户查看，数据如果也以列优先存储，在处理时内存上时连续的，提高缓存命中率，能提高效率。  
这也是我使用列优先的原因之二。  


## Array简要表示
```cpp
template<class T>  
class Array  
{  
    private:  
    std::vector<T> dim;  
    std::vector<T> data;  
    public:  
    ...other...  
};  
```

## 常用成员函数说明

```cpp
//构造一个空的Array
Array() noexcept {}
//构造一个只有一行的Array
Array(int row_) noexcept;
//通过包含维度信息的vector初始化Array的大小
Array(const std::vector<int> dims) noexcept;
//包含不同类型的Array间的拷贝
template<class ...K>Array(K ...arg);
//通过维度信息初始化Array的大小
template<typename T1, typename... T2>
void ArrayConstructor(T1 p, T2... arg);
//通过维度信息初始化Array的大小
void ArrayConstructor();
//通过initializer_list初始化
Array(std::initializer_list<T> list);
//获取元素
T& operator[](int n);
const T& operator[](int n)const;
//获取迭代器
typename std::vector<T>::iterator begin();
typename std::vector<T>::iterator end();
//const迭代器
typename std::vector<T>::const_iterator begin() const;
typename std::vector<T>::const_iterator end() const ;
typename std::vector<T>::const_iterator cbegin() const ;
typename std::vector<T>::const_iterator cend() const ;
//获取数据量
int size() const ;
//获取维度数组
std::vector<int> & get_dim() ;
std::vector<int> get_dim() const;
//获取数据数组
std::vector<T> & get_data();
std::vector<T> get_data() const;
//维度
int dim_size()const ;
//获取某一维大小
int get_dim_data(int n) const;
//从0到n维大小的乘积
int get_dim_acc(int n)const;
//重新分配Array大小
template<typename T1, typename... T2>
void resize(T1 p, T2... arg);
template<typename T1, typename... T2>
void resize_impl(T1 p, T2... arg);
void resize_impl();

void resize(const std::vector<int> & sz);

void resize(const Array<int> & sz);
//通过dim数组重新resize data数组，通常在手动改完dim后使用
void resize_from_dim();
//填充某数据
void fill(const T& val);
//是否为矩阵
bool isMatrix()const;
//是否是向量
bool isVector()const;
//是否只有一行
bool isRow()const;
//是否只有一列
bool isCol()const;
//是否为空
bool isEmpty()const;
```





