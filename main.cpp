#include<iostream>
#include<vector>
#include<ctime>
#include"BinarySearchTree.h"
using namespace std;

/**
 *  对数组进行BSTSorting
 */
template <typename Comparable>
void BSTSorting(std::vector<Comparable> &_arr, int _mode = 0)
{
    if(_mode == 1) //当数组进行乱序
    {
        random_shuffle(_arr.begin(),_arr.end()); //将数组乱序
        cout << "开始进行 _mode = 1（乱序）的排序，数组的大小为" << _arr.size() 
             << "，重复进行10次后取平均值。" << endl;
        BinarySearchTree<Comparable> bst; //构造一个二叉搜索树bst
        double average_duration; //创建一个double类的平均时长
        for(int j=1; j<=10; j++) //为了得到平均时长因此使用for循环
        {
            clock_t begin_time = clock(); //将起始时间赋值于begin_time
            for(int i=0; i < _arr.size(); i++) //将_arr中的元素一个一个插入bst
                bst.insert(_arr[i]); 
            clock_t end_time = clock(); //将终止时间赋值于end_time
            average_duration += (double)(end_time - begin_time)/CLOCKS_PER_SEC; 
            //累加每一次循环所得到的时长
        }
        average_duration /= 10; //上面进行了10次循环，因此这里除10
        cout << "排序结束，平均排序时长为" << average_duration << "秒。\v" << endl;
    }
    else //当数组不进行乱序
    {
        cout << "开始进行 _mode = 0（不乱序）的排序，数组的大小为" << _arr.size() 
             << "。" << endl;
        BinarySearchTree<Comparable> bst; //构造一个二叉搜索树bst
        clock_t begin_time = clock(); //将起始时间赋值于begin_time
        for(int i=0; i < _arr.size(); i++) //将_arr中的元素一个一个插入bst
            bst.insert(_arr[i]);
        clock_t end_time = clock(); //将终止时间赋值于end_time
        double duration = (double)(end_time - begin_time)/CLOCKS_PER_SEC;
        ////创建一个double类的时长，并将终止时间减去起始时间赋值于它
        cout << "排序结束，排序时长为" << duration << "秒。\v" << endl;
    }

    return;
}

void mode0_test(int n) //用于测试 _mode = 0 的最坏效率
{
  vector<double> _arr; //构造一个向量_arr
  
  for(int i = 1; i <= n; i++) //通过for循环将元素1到n依次插入_arr
     _arr.push_back(i); //数组中的元素正序时，时间效率最低
     
  BSTSorting(_arr, 0); //调用BSTSorting函数来排序_arr
}

void mode1_test(int n) //用于测试 _mode = 1 的平均效率
{
  vector<double> _arr; //构造一个向量_arr
  
  for(int i = 1; i <= n; i++) //通过for循环将元素1到n依次插入_arr
    _arr.push_back(i);

  BSTSorting(_arr, 1);  //调用BSTSorting函数来排序_arr
}


int main()
{
  for(int i = 10000; i <= 50000; i+=10000) //调用测试函数，进行五次不同大小的数组排序
        mode0_test(i);
        
  for(int i = 10000; i <= 50000; i+=10000) //调用测试函数，进行五次不同大小的数组排序
        mode1_test(i);

  return 0;
}

