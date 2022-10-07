#include<iostream>

template <typename DT>
class DoubleLinkedList //双链表的类
{
    private:
        struct Node //节点的结构
        {
            DT data; //数据
            Node *prev; //指向前一个节点的指针
            Node *next; //指向后一个节点的指针

            Node( const DT & d = DT{ }, Node * p = nullptr, Node * n = nullptr )  //节点构造函数，参数分别为左值和两个指针，前者默认值为空，后者默认值为空指针nullptr
            : data{ d }, prev{ p }, next{ n } { } //参数d、p和n分别赋值给data、prev和next

            Node( DT && d, Node * p = nullptr, Node * n = nullptr )  //节点构造函数，参数分别为左值和两个指针，后者默认值为空指针nullptr
            : data{ std::move( d ) }, prev{ p }, next{ n } { } //参数d、p和n分别赋值给data、prev和next，其中std::move的作用是将左值强制转换为右值引用
        };

    public:
        class const_iterator //常量迭代器的类，储存一个指向当前节点的迭代器，且重载运算符以实现基本的迭代器运算
        {
            public:
                const_iterator( ) : current{ nullptr } //将current指针初始化为nullptr的常量迭代器的构造函数
                { } 
                
                const DT & operator* ( ) const //单目运算符*的重载函数
                { return retrieve( ); } //返回当前常量迭代器类中current节点的数据
                
                const_iterator & operator++ ( ) //自增运算符++（前置）的重载函数
                {
                    current = current->next; //将常量迭代器类中的current指针指向当前所指的位置的下一个位置
                    return *this; //返回常量迭代器类中的current指针当前所指的位置的下一个位置的地址;
                }
                
                const_iterator operator++ ( int ) //自增运算符++（后置）的重载函数
                {
                    const_iterator old = *this; //将常量迭代器类中的this指针当前所指的位置的地址赋予常量迭代器old
                    ++( *this ); //调用了上面的重载函数
                    return old; //返回常量迭代器类中的this指针原先所指的位置的地址
                }
                
                bool operator== ( const const_iterator & rhs ) const //关系运算符==的重载函数
                { return current == rhs.current; } //比较当前常量迭代器类中的current指针与常量迭代器rhs的当前位置，如果相同，则返回真
                
                bool operator!= ( const const_iterator & rhs ) const //关系运算符!=的重载函数
                { return !( *this == rhs ); } //比较当前常量迭代器类中的this指针与常量迭代器rhs的当前位置，如果不相同，则返回真

            protected:
                Node *current; //指向当前位置的指针

                DT & retrieve( ) const
                { return current->data; } //返回当前位置的数据

                const_iterator( Node *p ) : current{ p }  //将current指针初始化为p的常量迭代器的构造函数
                { }

                friend class DoubleLinkedList<DT>; //使得常量迭代器类中的函数成员成为双链表类中的友元函数
        };

        class iterator : public const_iterator //迭代器的类，继承了常量迭代器的类
        {
            public: 
            
                iterator( ) //初始化为空的迭代器的构造函数
                { }

                DT & operator* ( ) //单目运算符*的重载函数，适用于传入非const list
                { return const_iterator::retrieve( ); } //返回当前常量迭代器类中current节点的数据
                
                const DT & operator* ( ) const //单目运算符*的重载函数，适用于传入const list的情况
                { return const_iterator::operator*( ); } //返回当前常量迭代器类中current节点的数据

                iterator & operator++ ( ) //自增运算符++（前置）的重载函数
                {
                    this->current = this->current->next; //将迭代器类中的this指针指向当前所指的位置的下一个位置
                    return *this; //返回迭代器类中的this指针当前所指的位置的下一个位置的地址;
                }

                iterator operator++ ( int ) //自增运算符++（后置）的重载函数
                {
                    iterator old = *this; //将迭代器类中的this指针当前所指的位置的地址赋予迭代器old
                    ++( *this ); //调用了上面的重载函数
                    return old; //返回迭代器类中的this指针原先所指的位置的地址
                }

            protected:
                iterator( Node *p ) : const_iterator{ p } //将常量迭代器的类初始化为p的迭代器的构造函数
                { }

                friend class DoubleLinkedList<DT>; ////使得迭代器类中的函数成员成为双链表类中的友元函数
        };

    public:
        DoubleLinkedList( ) //创建未传参数的双链表
        { init( ); }
        
        DoubleLinkedList( const DoubleLinkedList & rhs ) //构造函数的复制
        { 
            init( );  
            for( auto & x : rhs )
            push_back( x ); 
        }
        
        ~DoubleLinkedList( ) //析构函数，用于释放内存空间，避免内存泄漏
        {
            clear( );
            delete head;
            delete tail;
        }
        
        DoubleLinkedList & operator= ( const DoubleLinkedList & rhs ) //赋值运算符=的重载函数，参数为左值双链表
        { 
            DoubleLinkedList copy = rhs;
            std::swap( *this, copy ); //交换指针this与copy的地址
            return *this; //返回指针this指向的数据;
        }
            
        DoubleLinkedList( DoubleLinkedList && rhs ) // 双链表的构造函数，参数为右值双链表
            : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
        {
            rhs.theSize = 0;
            rhs.head = nullptr;
            rhs.tail = nullptr;
        }
        
        DoubleLinkedList & operator= ( DoubleLinkedList && rhs ) //赋值运算符=的重载函数，参数为右值双链表
        { 
            std::swap( theSize, rhs.theSize );
            std::swap( head, rhs.head );
            std::swap( tail, rhs.tail );

            return *this; //返回指针this指向的数据;
        }
 
        iterator begin( ) //begin函数，调取双链表头节点的下一个位置
        { return { head->next }; } //返回 head->next 的迭代器
        
        const_iterator begin( ) const //begin函数的重载，调取const双链表头节点的下一个位置
        { return { head->next }; } //返回 head->next 的常量迭代器
            
        iterator end( ) //end函数，调取双链表的尾结点的上一个位置
        { return { tail }; } //返回 tail 的迭代器
        
        const_iterator end( ) const //end函数的重载，调取const双链表尾节点的上一个位置
        { return { tail }; } //返回 tail 的常量迭代器

        int size( ) const //size函数，调取双链表的大小（长度、亦或是节点个数）
        { return theSize; }  //返回双链表的大小（整型）
        
        bool empty( ) const //empty函数，判断双链表是否为空
        { return size( ) == 0; } //若双链表为空，则返回真

        void clear( ) //clear函数，清空双链表（清空后双链表依旧存在，只是内容为空）
        {
            while( !empty( ) ) //不停地删除双链表开头的节点直到双链表为空
            pop_front( ); 
        }
        
        DT & front( ) //front函数，调取双链表头节点的下一个位置的数据
        { return *begin( ); }  //返回双链表头节点的下一个位置的数据
        
        const DT & front( ) const //front函数的重载，调取双链表头节点的下一个位置的数据
        { return *begin( ); } //返回双链表头节点的下一个位置的数据
        
        DT & back( ) //back函数，调取双链表尾节点的位置的上一个位置的数据
        { return *--end( ); } //返回双链表尾节点的位置的上一个位置的数据
        
        const DT & back( ) const //back函数的重载，调取双链表尾节点的位置的上一个位置的数据
        { return *--end( ); } //返回双链表尾节点的位置的上一个位置的数据
        
        void push_front( const DT & x ) //push_front函数，将DT类的左值数据x插入在双链表头节点的下一个位置
        { insert( begin( ), x ); } 
        
        void push_front( DT && x ) //push_front函数的重载，将DT类的右值数据x插入在双链表头节点的下一个位置
        { insert( begin( ), std::move( x ) ); }
        
        void push_back( const DT & x ) //push_back函数，将DT类的左值数据x插入在双链表尾结点的上一个位置
        { insert( end( ), x ); } 
        
        void push_back( DT && x ) //push_back函数的重载，将DT类的右值数据x插入在双链表尾结点的上一个位置
        { insert( end( ), std::move( x ) ); }
        
        void pop_front( ) //pop_front函数，将双链表头节点的下一个节点删除
        { erase( begin( ) ); }
        
        void pop_back( ) //pop_front函数，将双链表尾节点的上一个节点删除
        { erase( --end( ) ); }

        iterator insert( iterator itr, const DT & x ) //insert函数，在双链表中的迭代器itr位置前插入DT类的左值数据为x的新节点
        { 
            Node *p = itr.current;
            theSize++;
            return { p->prev = p->prev->next = new Node{ x, p->prev, p } };  //返回插入新节点后的迭代器
        }
            
        iterator insert( iterator itr, DT && x ) //insert函数的重载，在双链表中的迭代器itr位置前插入DT类的右值数据为x的新节点
        { 
            Node *p = itr.current;
            theSize++;
            return { p->prev = p->prev->next = new Node{ std::move( x ), p->prev, p } }; //返回插入新节点后的迭代器
        }

        iterator erase(iterator itr) //erase函数，将双链表中的迭代器itr位置的节点删除
        {
            Node *p = itr.current;
            iterator retVal{ p->next }; 
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete p;
            theSize--;
            
            return retVal; //返回删除指定节点后的迭代器
        }
        
        iterator erase(iterator from, iterator to) //erase函数，将双链表中从位置from到位置to的一整段节点删除（一个一个删）
        {
            for( iterator itr = from; itr != to; ) 
                itr = erase( itr );
                
            return to; //返回删除指定节点后的迭代器
        }
        
        void printList() //printList函数，在终端上输出输出指定的双链表
        {
            for (iterator itr = begin(); itr != end(); itr++)
            {
                std::cout << *itr << " ";
            }
            std::cout << '\b' << std::endl;
        }

    private:
        int theSize; //双链表的大小（长度，亦或是节点个数）
        Node *head; //指向头节点的指针
        Node *tail; //指向尾节点的指针

        void init( ) //双链表的初始化函数
        { 
            theSize = 0;
            head = new Node;
            tail = new Node;
            head->next = tail;
            tail->prev = head; 
        }
};