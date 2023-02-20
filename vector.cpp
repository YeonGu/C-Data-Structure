/**
 * @file    vector.cpp
 * @author  Gu Yuhang
 * @brief   基于C++实现的vector数据结构
 * @version 0.1
 * @date    2023-02-14
 *
 * @copyright Copyright (c) 2023, Yuhang Gu
 *
 */

/* vector的抽象数据接口定义：
   构造和析构函数
*/
#include <iostream>
#include <ostream>
#include <vcruntime_string.h>

#define DEFAULT_CAPACITY 3

using Rank = int;

/**
 *  @brief  Vector相关ADT接口
 *
 *  @tparam typename T
 */

template <typename T>
class Vector {
  protected:
    int _capacity;
    Rank _size;
    T* _element; // 指向元素存储区的指针

  protected:
    void CopyFrom(const T* const src, Rank lo,
                  Rank hi);            // copy vector from array in [lo, hi)
    void Expand();                     // 扩容
    void Shrink();                     // 压缩
    bool Bubble(Rank lo, Rank hi);     // 扫描交换
    void BubbleSort(Rank lo, Rank hi); // 冒泡排序
    Rank Max(Rank lo, Rank hi);
    void SelectionSort(Rank lo, Rank hi); // 选择排序
    void Merge(Rank lo, Rank hi);         // 归并算法
    void MergeSort(Rank lo, Rank hi);     // 归并排序
    Rank Partition(Rank lo, Rank hi);     // 轴点构造算法
    void QuickSort(Rank lo, Rank hi);     // 快速排序算法
    void HeapSort(Rank lo, Rank hi);      // 堆排序

  public:
    // Constructors 构造函数
    Vector(int cap = DEFAULT_CAPACITY, int size = 0, T initVal = 0) {
        _element = new T[_capacity = cap];
        for (_size = 0; _size < size; _element[_size++] = initVal)
            ;
    }
    Vector(const T* const src, Rank n) { CopyFrom(src, 0, n); }             // 从数组整体复制
    Vector(const T* const src, Rank lo, Rank hi) { CopyFrom(src, lo, hi); } // 从数组区间复制
    Vector(Vector<T> const& v) { CopyFrom(v._element, 0, v._size); }        // 从Vector拷贝
    Vector(Vector<T> const& v, Rank lo, Rank hi) { CopyFrom(v._element, lo, hi); }
    ~Vector() { delete[] _element; }

    // Read-only access interface 只读访问接口
    Rank Size() const { return _size; }
    bool Empty() const { return !_size; }
    int Disordered() const;                        // 判断是否已经排序
    Rank Find(T const& t, Rank lo, Rank hi) const; // 无序向量查找
    Rank Find(T const& t) { return Find(t, 0, _size); }
    Rank Search(T const& t, Rank lo, Rank hi) const; // 有序向量查找
    Rank Search(T const& t) const {
        return (_size <= 0) ? -1 : Search(t, 0, _size);
    }

    // Writable access interface 可写访问接口
    T& operator[](Rank r) const;              // 重载下标
    Vector<T>& operator=(Vector<T> const& v); // 重载赋值
    T Remove(Rank r);
    Rank Insert(Rank r, T const& e);
    Rank Insert(T const& e);
    void Sort(Rank lo, Rank hi);
    void Sort() { Sort(0, _size); }
    void Unsort(Rank lo, Rank hi); // 对元素置乱
    void Unsort() { Unsort(0, _size); }
    void Deduplicate(); // 无序去重
    void Uniquify();    // 有序去重

    // 遍历
    // void Traverse

    friend std::ostream& operator<<(std::ostream& stream, Vector<T> const& e);
};

/**
 * @brief 数组整体复制
 *
 * @tparam T
 * @param src
 * @param lo
 * @param hi
 */
// template <typename T> // 复制的向量构造器
// void Vector<T>::CopyFrom(const T* const src, Rank lo, Rank hi) {
//     _element = new T[_capacity = (hi - lo) * 2]; // 新的规模、大小和内容
//     _size = hi - lo;
//     memcpy(_element, src, hi - lo);
// }

template <typename T>
void Vector<T>::Expand() {
    if (_size < _capacity)
        return;
    if (_capacity < DEFAULT_CAPACITY)
        _capacity = DEFAULT_CAPACITY;
    T* oldElement = _element;
    _element = new T[_capacity <<= 1];
    memcpy(_element, oldElement, _size);
    delete[] oldElement;
}

// 重载赋值运算符
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v) {
    if (_element)
        delete[] _element;
    CopyFrom(v._element, 0, v._size);
    return *this;
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, Vector<T> const& e) {
    for (int i = 0; i < e->_size; i++) {
        stream << *(e->_element + i) << ", ";
    }
    return stream;
}

int main() {}