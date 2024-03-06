#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Fraction
{
    friend Fraction operator+(const Fraction& frac1, const Fraction& frac2)                         //重载+运算符
    {
        Fraction result;
        result.numer = frac1.numer * frac2.deno + frac2.numer * frac1.deno;
        result.deno = frac1.deno * frac2.deno;
        result.RdcFrc(result);
        return result;
    }
    friend Fraction operator-(const Fraction& frac1, const Fraction& frac2)                         //重载-运算符
    {
        Fraction result;
        result.numer = frac1.numer * frac2.deno - frac2.numer * frac1.deno;
        result.deno = frac1.deno * frac2.deno;
        result.RdcFrc(result);
        return result;

    }
    friend Fraction operator*(const Fraction& frac1, const Fraction& frac2)                         //重载*运算符
    {
        Fraction result;
        result.numer = frac1.numer * frac2.numer;
        result.deno = frac1.deno * frac2.deno;
        result.RdcFrc(result);
        return result;
    }
    friend Fraction operator/(const Fraction& frac1, const Fraction& frac2)                         //重载/运算符
    {
        Fraction result;
        result.numer = frac1.numer * frac2.deno;
        result.deno = frac1.deno * frac2.numer;
        result.RdcFrc(result);
        return result;
    }
    friend bool operator==(Fraction frac1, Fraction frac2 )                                         //重载==运算符
    {
        Fraction Frac1;
        Fraction Frac2;
        Frac1.RdcFrc(frac1);
        Frac2.RdcFrc(frac2);
        return(Frac1.numer == Frac2.numer && Frac1.deno == Frac2.deno);
    }
    friend bool operator>(const Fraction& frac1, const Fraction& frac2)                             //重载>运算符
    {
        return (double(frac1.numer) / frac1.deno > double(frac2.numer) / frac2.deno);
    }
    friend bool operator<(const Fraction& frac1, const Fraction& frac2)                             //重载<运算符
    {
        return (double(frac1.numer) / frac1.deno < double(frac2.numer) / frac2.deno);
    }
    friend ostream& operator<<(ostream& out, const Fraction& frac)                                  //重载<<运算符
    {
        cout << frac.numer << "/" << frac.deno;
        return out;
    }
    friend istream& operator>>(istream& in, Fraction& frac)                                         //重载>>运算符
    {
        char split;  // 分数线
        in >> frac.numer >> split >> frac.deno;
        return in;
    }
    friend void sortFraction(vector<Fraction>& v, char sign)                                        //对分数数组排序
    {
        if (sign == '>')
        {
            sort(v.begin(), v.end(), greater<>());//利用sort函数以及vector容器排序
        }
        else if (sign == '<')
        {
            sort(v.begin(), v.end(), less<>());
        }
    }
public:
    Fraction()                                                                                      //无参造函数
    {
    }
    Fraction(int n, int d)                                                                          //带参造函数
    {
        numer = n;
        deno = d;
    }
    Fraction(const Fraction& f)                                                                     //复制造函数
    {
        numer = f.numer;
        deno = f.deno;
    }
    void setFraction(int n, int d)                                                                  //设置分数的分子和分母
    {
        numer = n;
        deno = d;
    }
    int getNumer()                                                                                  //获取分数的分子
    {
        return numer;
    }
    int getDeno()                                                                                   //获取分数的分母
    {
        return deno;
    }
    int findgcd(int a, int b)                                                                       //寻找最大公约数
    {
        return b == 0 ? a : findgcd(b, a % b);
    }
    Fraction RdcFrc(Fraction& FRAC)                                                                 //当前分数约分
    {
        int gcd = findgcd(abs(FRAC.numer), abs(FRAC.deno));
        FRAC.numer = FRAC.numer / gcd;
        FRAC.deno = FRAC.deno / gcd;
        return FRAC;
    }
private:
    int numer; //分子
    int deno;  //分母    
};

void Calculationinterface()                                                                        //分数计算界面
{
    while (true)
    {
        cout << "请输入分数计算式（如1/2+1/3回车），输入#号键返回上一层目录：" << endl;
        Fraction frac1;
        Fraction frac2;
        char sign;
        cin >> frac1 >> sign >> frac2;
        while (cin.fail())//当输入的类型不是char时进入循环
        {                       
            cin.clear();//清楚此时fail的状态
            if (cin.peek() == '#')
            {
                cin.get();//取走缓冲区中的\n
                system("cls");//清屏
                return;
            }
            cin.get();
            cout << "输入错误！" << endl;
            cin >> frac1 >> sign >> frac2;
        }
        Fraction result;
        switch (sign)//利用switch来确定计算类型并得出结果
        {
        case ('+'):
            result = frac1 + frac2;
            break;
        case ('-'):
            result = frac1 - frac2;
            break;
        case('*'):
            result = frac1 * frac2;
            break;
        case('/'):
            result = frac1 / frac2;
            break;
        default:
            break;
        }
        cout << "=" << result << endl;
    }
}
void Sortinterface()                                                                              //分数排序界面
{
    while (true)
    {
        cout << "请输入一组分数，用逗号隔开，如需由小到大排序用符号<结尾，由大到小排序用符号>结尾（如1/2，1/4，3/5<回车），输入#号键返回上一层目录：" << endl;
        vector<Fraction>  v;//使用vector容器，为动态数组
        char sign;
        Fraction temp;
        while (true)
        {
            cin >> temp >> sign;
            while (cin.fail() || (sign != ',' && sign != '<' && sign != '>'))
            {
                cin.clear();
                if (cin.peek() == '#')
                {
                    cin.get();
                    system("cls");
                    return;
                }
                cout << "输入错误！" << endl;
                cin.get();
                cin >> temp >> sign;
            }
            v.push_back(temp);//在v的第一个元素位置插入temp
            if (sign == '<' || sign == '>')
            {
                break;
            }
        }
        sortFraction(v, sign);
        for (int i = 0; i < v.size(); i++)//使用size()获得vector容器v的长度，即元素个数
        {
            cout << v[i] << " ";
        }
        cout << endl;
    }
}
void maininterface()                                                                              //主界面
{
    while (true)
    {
        cout << "请选择功能（键入1或者2）：" << endl;
        cout << "1.分数计算" << endl;
        cout << "2.分数排序" << endl;
        int number1;
        cin >> number1;
        while (cin.fail())
        {
            cin.clear();
            cout << "输入错误！" << endl;
            void maininterface();
            cin.get();
            cin >> number1;
        }
        if (number1 == 1)
        {
            system("cls");
            Calculationinterface();
        }
        else if (number1 == 2)
        {
            system("cls");
            Sortinterface();
        }
        else
        {
            break;
        }
    }
}
int main()
{
    while (true)
    {
        system("cls");
        maininterface();
    }
    return 0;
}
