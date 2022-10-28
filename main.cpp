#include<iostream>
#include<random>
#include<ctime>

#include "AvlTree.h"

using namespace std;

void test(int j) //j为题目中的N
{
    clock_t start, finish; //start用于记录函数开始之前之前的时间，finish用于记录函数进行结束后的时间
    
    int k1, k2; //k1与k2皆用于设定打印出的数据区间
    
    AvlTree<int> T; //创建一个新的AvlTree
    
    for( int i = 1; i <= j; i++) //将1到N的数字加入到AvlTree中
    {
        T.insert(i);
    }
    
    k1=rand()%(j/2); //设置区间下确界k1，确保它小于N/2
    
    k2=rand()%(j/2)+(j/2); //设置区间上确界k2，确保它大于N/2
    
    cout << "当 k1 = " << k1 << "，k2 = " << k2 << " 时：" << endl; //显示下确界k1与上确界k2的值
    
    cout << "区间内的数据：";
    
    start = clock();
    
    T.printbetween( k1, k2 );
    
    finish = clock();
    
    cout << endl;
    
    cout << "打印出区间内数据的所需时间为: "<< double(finish - start)*1000 / CLOCKS_PER_SEC << "毫秒。" << endl;
    
    cout << endl;
    
    return;
}

int main() 
{
    for( int i = 10; i <= 10000; i *= 10)
        test(i);

    return 0;
} 