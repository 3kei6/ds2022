#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

string dTOs( double d ) //转换函数（将double转换成string）
{
    stringstream ss;
    string s;
    ss << d;
    ss >> s;
    return s;
}

double sTOd( string& s ) //转换函数（将string转换成double）
{
    istringstream iss(s);
    double d;
    iss >> d;
    return d;
}

double sTOd( string&& s ) //转换函数（将string转换成double）
{
    istringstream iss(s);
    double d;
    iss >> d;
    return d;
}

int type( char & c )
{
    if( c >= '0' && c <= '9' ) //若参数为数字，则返回1
    {
        return 1;
    }
    
    else if( c == '+' || c == '-' || c == '*' || c =='/' || c == '^' ) //若参数为运算符，则返回2
    {
        return 2;
    }
    
    else if ( c== '.' || c == '(' || c == ')' ) //若参数为符号，则返回3
    {
        return 3;
    }
    
    else //若参数为其他，则返回-1
    {
        return -1;
    }
}

bool is_valid( string & s )
{
    int d = 0;
    
    for( int i = 0; i < s.size(); i++ )
    {
        if( type(s[i]) != -1 )
        {
            if( type(s[i]) == 2 && ( ( i == 0 && s[i] != '-' )  || i == s.size() || ( type(s[i+1]) != 1 && s[i+1] != '(' ) || ( type(s[i-1]) != 1 && s[i-1] != ')' && s[i] != '-' ) ) ) 
            {
                cerr << "错误：无效的运算符位置" << endl;
                return false;
            }

            else if( s[i] == '.' && ( i == 0 || i == s.size() || type(s[i+1]) != 1 || type(s[i-1]) != 1 ) )
            {
                cerr << "错误：无效的小数点位置" << endl;
                return false;
            }

            else if( s[i] == '/' && s[i+1] == '0' ) 
            {
                cerr << "错误：除数为0" << endl;
                return false;
            }
            
            else if( s[i] == '(' )
            {
                if( s[i+1] != ')' ) 
                {
                    d++;
                }
                
                else
                {
                    cerr << "错误：无效的括号内容" << endl;
                    return false;
                }
            }
                
            else if( s[i] == ')' ) 
            {
                d--;
            }
        }   
        
        else
        {
            cerr << "错误：存在无效字符" << endl;
            return false;
        }

        if( d < 0 )
        {
            cerr << "错误：括号不匹配" << endl;
            return false;
        }
    }
    
    if( d != 0 )
    {
        cerr << "错误：无效的括号数量" << endl;
        return false;
    }
    
    return true;
}

class ExpressionTree
{
    public:
        ExpressionTree( ) : root{ nullptr } //构造函数
        {}
    
        ~ExpressionTree( ) //析构函数
        {
            clear( );
        }
        
        void insert( const string & s ) //插入函数
        {
            insert( s, root );
        }
        
        void clear( ) //清除函数
        {
            clear( root );
        }
        
        string calculate( ) //计算函数
        {
            calculate( root );
            return root->element;
        }

    private:
        struct ExpressionNode //节点结构
        {
            string element; //元素值
            
            ExpressionNode *left; //指向左子树的指针
            
            ExpressionNode *right; //指向的右子树的指针
     
            ExpressionNode( const string & e, ExpressionNode *ln, ExpressionNode *rn ): element{ e }, left{ ln }, right{ rn } { }
              
            ExpressionNode( string && e, ExpressionNode *ln, ExpressionNode *rn ): element{ std::move( e ) }, left{ ln }, right{ rn } { }
        };
    
        ExpressionNode *root;
    
    	int priority( string s ) //运算符的优先级判断函数
    	{
    		if ( s == "+" || s == "-" )
    		{
    		    return 0;
    		}
    		
    		else if( s == "*" || s == "/" )
    		{
    		    return 1;
    		}
    		
    		else if( s == "^" )
    		{
    		    return 2;
    		}
    		
            else 
            {
                return 3;
            }
    	}

        void insert( const string & s, ExpressionNode *&en )
        {
            if( en == nullptr )
            {
                en = new ExpressionNode{ s, nullptr, nullptr };
            }
            
            else if( priority(s) <= priority(en->element) && en->right != nullptr && ( priority(s) != 2 || priority(en->element) != 2 ) )
            {
                insert( s, en->left );
                en->left->left = en->left->right;
                en->left->right = en;
                en = en->left;
                en->right->left = en->left;
                en->left = nullptr;
            }
            
            else if( priority(s) <= priority(en->element) && en->right == nullptr && ( priority(s) != 2 || priority(en->element) != 2 ) )
            {
                insert( s, en->right );
                en->right->right = en;
                en = en->right;
                en->right->right = nullptr;
            }
        
            else if( priority(s) == 2 && priority(en->element) == 2 )
            {
                insert( s, en->left );
            }
            
            else if( priority(s) > priority(en->element) && en->right != nullptr )
            {  
                insert( s, en->left );
            }
           
            else if( priority(s) > priority(en->element) && en->right == nullptr )
            {  
                insert( s, en->right );
            }
        }
        
        void clear( ExpressionNode * &t )
        {
            if( t != nullptr )
            {
                clear( t->left );
                clear( t->right );
                delete t;
            }
            
            t = nullptr;
        }
    
        void calculate( ExpressionNode *t )
        {
            if( type((t->element)[0]) == 2 && t->element.size() == 1 && !( t->element== "/" && sTOd(t->left->element) == 0 ) )
            {
                calculate(t->left);
                calculate(t->right);
                t->element = result(t);
            }
            else if( t->element == "/" && sTOd(t->left->element) == 0 )
            {
                cerr << "错误：除数为0" << endl;
                t->element = " ";
            }
        }
    
        string result( ExpressionNode * & t )
        {
            if( t->left->element == " " || t->right->element == " " )
            {
                return " ";
            }
            
            else if( t->element == "+" )
            {
                return dTOs( sTOd(t->right->element) + sTOd(t->left->element) );
            }
            
            else if( t->element == "-" )
            {
                return dTOs( sTOd(t->right->element) - sTOd(t->left->element) );
            }
            
            else if( t->element == "*" )
            {
                return dTOs( sTOd(t->right->element) * sTOd(t->left->element) );
            }
            
            else if( t->element == "/" )
            {
                return dTOs( sTOd(t->right->element) / sTOd(t->left->element) );
            }
            
            else if( t->element == "^" )
            {
                return dTOs( pow(sTOd(t->right->element), sTOd(t->left->element)) );
            }
            
            else
                return " ";
        }
};

string calculate( string &s )
{
    string* numbers = new string[s.size()];
    
    string* sign = new string[s.size()];
    
    int j = 0;
    
    ExpressionTree ET;
    
    for( int i = 0; i < s.size(); i++ )
    {
        string t = "";
        
        if( s[i] == '(' )
        {
            int p = 1;
            
            int q = i;
            
            while( p != 0 && q < s.size() )
            {
                q++;
                
                if( s[q] == '(' )
                {
                    p++;
                }
                
                if( s[q] == ')' )
                {
                    p--;
                }
            }
            
            for( int k = i + 1; k < q; k++ )
            {
                t.push_back(s[k]);
            }
            
            numbers[j] = calculate(t);
            
            i = q;
        }
        
        else if( s[i] == '-' && type(s[i-1]) != 1 && s[i-1] != ')' )
        {
            numbers[j] = '-';
        }
        
        else if( s[i] >= '0' && s[i] <= '9' || s[i] == '.' )
        {
            numbers[j] += s[i];
        }
        
        else if( type(s[i]) == 2 )
        {
            sign[j] = s[i];
            
            j++;
        }
    }
    
    for( int k = 0; k < j; k++ )
    {
        ET.insert(numbers[k]);
        ET.insert(sign[k]);
    }
    
    ET.insert(numbers[j]);

    return ET.calculate();
}