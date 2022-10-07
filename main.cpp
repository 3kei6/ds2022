#include "DoubleLinkedList.h"

template <typename DT>
typename DoubleLinkedList<DT>::iterator find(DoubleLinkedList<DT>& _list, const DT& _val)
{
    typename DoubleLinkedList<DT>::iterator itr = _list.begin();
    typename DoubleLinkedList<DT>::iterator end = _list.end();
    int position = 1;
    for(itr; itr != end; ++itr)
    {
        if(*itr == _val)
        {
            std::cout << "The position of value \"" << _val << "\" is " << position << "." << std::endl;
            return itr;
        }
        position++;
    }
    std::cout << "The given value \"" << _val << "\" is not found in the list!" << std::endl;
    return itr;
};

int main(int argc, char* argv[])
{
    DoubleLinkedList<int> L;
    L.push_back(1);
    L.push_back(2);
    L.push_back(3);
    L.push_back(4);
    L.push_back(5);
    L.printList();
    DoubleLinkedList<int>::iterator iter;
    iter = find(L, 3);
    L.erase(iter);
    L.printList();
    iter = find(L, 3);
    return 0;
}