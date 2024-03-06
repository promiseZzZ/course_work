#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Fraction
{
    friend Fraction operator+(const Fraction& frac1, const Fraction& frac2)                         //����+�����
    {
        Fraction result;
        result.numer = frac1.numer * frac2.deno + frac2.numer * frac1.deno;
        result.deno = frac1.deno * frac2.deno;
        result.RdcFrc(result);
        return result;
    }
    friend Fraction operator-(const Fraction& frac1, const Fraction& frac2)                         //����-�����
    {
        Fraction result;
        result.numer = frac1.numer * frac2.deno - frac2.numer * frac1.deno;
        result.deno = frac1.deno * frac2.deno;
        result.RdcFrc(result);
        return result;

    }
    friend Fraction operator*(const Fraction& frac1, const Fraction& frac2)                         //����*�����
    {
        Fraction result;
        result.numer = frac1.numer * frac2.numer;
        result.deno = frac1.deno * frac2.deno;
        result.RdcFrc(result);
        return result;
    }
    friend Fraction operator/(const Fraction& frac1, const Fraction& frac2)                         //����/�����
    {
        Fraction result;
        result.numer = frac1.numer * frac2.deno;
        result.deno = frac1.deno * frac2.numer;
        result.RdcFrc(result);
        return result;
    }
    friend bool operator==(Fraction frac1, Fraction frac2 )                                         //����==�����
    {
        Fraction Frac1;
        Fraction Frac2;
        Frac1.RdcFrc(frac1);
        Frac2.RdcFrc(frac2);
        return(Frac1.numer == Frac2.numer && Frac1.deno == Frac2.deno);
    }
    friend bool operator>(const Fraction& frac1, const Fraction& frac2)                             //����>�����
    {
        return (double(frac1.numer) / frac1.deno > double(frac2.numer) / frac2.deno);
    }
    friend bool operator<(const Fraction& frac1, const Fraction& frac2)                             //����<�����
    {
        return (double(frac1.numer) / frac1.deno < double(frac2.numer) / frac2.deno);
    }
    friend ostream& operator<<(ostream& out, const Fraction& frac)                                  //����<<�����
    {
        cout << frac.numer << "/" << frac.deno;
        return out;
    }
    friend istream& operator>>(istream& in, Fraction& frac)                                         //����>>�����
    {
        char split;  // ������
        in >> frac.numer >> split >> frac.deno;
        return in;
    }
    friend void sortFraction(vector<Fraction>& v, char sign)                                        //�Է�����������
    {
        if (sign == '>')
        {
            sort(v.begin(), v.end(), greater<>());//����sort�����Լ�vector��������
        }
        else if (sign == '<')
        {
            sort(v.begin(), v.end(), less<>());
        }
    }
public:
    Fraction()                                                                                      //�޲��캯��
    {
    }
    Fraction(int n, int d)                                                                          //�����캯��
    {
        numer = n;
        deno = d;
    }
    Fraction(const Fraction& f)                                                                     //�����캯��
    {
        numer = f.numer;
        deno = f.deno;
    }
    void setFraction(int n, int d)                                                                  //���÷����ķ��Ӻͷ�ĸ
    {
        numer = n;
        deno = d;
    }
    int getNumer()                                                                                  //��ȡ�����ķ���
    {
        return numer;
    }
    int getDeno()                                                                                   //��ȡ�����ķ�ĸ
    {
        return deno;
    }
    int findgcd(int a, int b)                                                                       //Ѱ�����Լ��
    {
        return b == 0 ? a : findgcd(b, a % b);
    }
    Fraction RdcFrc(Fraction& FRAC)                                                                 //��ǰ����Լ��
    {
        int gcd = findgcd(abs(FRAC.numer), abs(FRAC.deno));
        FRAC.numer = FRAC.numer / gcd;
        FRAC.deno = FRAC.deno / gcd;
        return FRAC;
    }
private:
    int numer; //����
    int deno;  //��ĸ    
};

void Calculationinterface()                                                                        //�����������
{
    while (true)
    {
        cout << "�������������ʽ����1/2+1/3�س���������#�ż�������һ��Ŀ¼��" << endl;
        Fraction frac1;
        Fraction frac2;
        char sign;
        cin >> frac1 >> sign >> frac2;
        while (cin.fail())//����������Ͳ���charʱ����ѭ��
        {                       
            cin.clear();//�����ʱfail��״̬
            if (cin.peek() == '#')
            {
                cin.get();//ȡ�߻������е�\n
                system("cls");//����
                return;
            }
            cin.get();
            cout << "�������" << endl;
            cin >> frac1 >> sign >> frac2;
        }
        Fraction result;
        switch (sign)//����switch��ȷ���������Ͳ��ó����
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
void Sortinterface()                                                                              //�����������
{
    while (true)
    {
        cout << "������һ��������ö��Ÿ�����������С���������÷���<��β���ɴ�С�����÷���>��β����1/2��1/4��3/5<�س���������#�ż�������һ��Ŀ¼��" << endl;
        vector<Fraction>  v;//ʹ��vector������Ϊ��̬����
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
                cout << "�������" << endl;
                cin.get();
                cin >> temp >> sign;
            }
            v.push_back(temp);//��v�ĵ�һ��Ԫ��λ�ò���temp
            if (sign == '<' || sign == '>')
            {
                break;
            }
        }
        sortFraction(v, sign);
        for (int i = 0; i < v.size(); i++)//ʹ��size()���vector����v�ĳ��ȣ���Ԫ�ظ���
        {
            cout << v[i] << " ";
        }
        cout << endl;
    }
}
void maininterface()                                                                              //������
{
    while (true)
    {
        cout << "��ѡ���ܣ�����1����2����" << endl;
        cout << "1.��������" << endl;
        cout << "2.��������" << endl;
        int number1;
        cin >> number1;
        while (cin.fail())
        {
            cin.clear();
            cout << "�������" << endl;
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
