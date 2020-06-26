/*
*positon:�������㷨���� p182
* date: 2018-09-11
*
*/
#include<iostream>
#include<string>
#include<iomanip>
#include<stack>
#include<cstdlib>
using namespace std;
typedef struct Node
{
    struct Node *left = nullptr;
    struct Node *right = nullptr;
    string name;
    string gender;
    string num;
    string date;
    int salary = 0;
    static int total;
    Node() {}
    Node(string na, string gen, string number, string da, int s)
    {
        name.assign(na);
        gender.assign(gen);
        num.assign(number);
        date.assign(da);
        salary = s;
        total++;
    }
    ~Node() {}
} Staff;
int Staff::total = 0;
void inOrderTraverse(Staff *r )      // �������BST
{   if(r == nullptr)
    {
        return;
    }

    /*if(r != nullptr) {          // �ݹ��������BST
        inOrderTraverse(r->left);
        cout << r->name << "\t" << r->gender << "\t" << r->num << "\t" << r->date << "\t" << r->salary << endl;
        inOrderTraverse(r->right);
    }*/
    // �ǵݹ�
    /*
        ������������������ѹջ��ֱ��Ҷ�ӽ�㣬��ҲΪ���ڵ㣬��ʱ��ʼ������ڵ㣨Ҷ�ӽ�㣩���ݲ���ջ�����������ʸø��ڵ��������������������
    */
    stack<Staff*> s;
    Staff *p=r;
    while(p != nullptr || !s.empty())   // �ǵݹ��������BST
    {
        while(p != nullptr)
        {
            s.push(p);
            p = p->left;
        }
        if(!s.empty())
        {
            p = s.top();
            cout << p->name << "\t" << p->gender << "\t" << p->num << "\t" << p->date << "\t" << p->salary << endl; //��ʱΪ
            s.pop();
            p = p->right;
        }
    }
}
void addStaff(Staff **r, string m[])    // ����ָ���ָ�룬�����κεط��޸�ָ��ָ��ĵ�ַ�����ݶ����÷��ء�
{
    /* if(nullptr == (*r))         // �ݹ�ʵ��
     {
         *r = new Staff(m[0], m[1], m[2], m[3], atoi(m[4].c_str()));
         cout << "���ְԱ�ɹ���" << endl;
         return;
     }
     if(m[2] < (*r)->num)
     {
         return addStaff(&(*r)->left, m);
     }
     else
     {
         return addStaff(&(*r)->right, m);
     }
     */
    /* �ǵݹ�ʵ�ֲ���ڵ㣬�Ƚϵ�ǰ�ڵ�ļ������Ľڵ�ļ���ֱ���ҵ�һ��С�ڵ�ǰ�ڵ���Ľڵ�������������Ϊ�ա�*/
    if(r == nullptr)
    {
        *r = new Staff(m[0], m[1], m[2], m[3], atoi(m[4].c_str()));
        cout<<"��ӳɹ�!"<<endl;
        return;
    }
    while(r != nullptr)
    {
        if(nullptr == (*r))
        {
            *r = new Staff(m[0], m[1], m[2], m[3], atoi(m[4].c_str()));
            cout<<"��ӳɹ�!"<<endl;
            break;
        }
        if(m[2] < (*r)->num)
        {
            r = &(*r)->left;
        }
        else
        {
            r = &(*r)->right;
        }
    }
}
int deleteStaff(Staff *&r,string num)
{
    if(nullptr == r)        // BSTΪ��
    {
        return -1;
    }
    if(r->num > num)        // ����������
    {
        return deleteStaff(r->left,num);
    }
    else if(r->num < num)   // ����������
    {
        return deleteStaff(r->right,num);
    }
    else
    {
        if(r->left == nullptr || r->right == nullptr)       // ɾ���Ľڵ�ֻ����������������
        {
            r = (r->left != nullptr)?r->left:r->right;
            return 1;
        }
        else
        {
            Staff *temp = r->right;      // ����������һ����С�ڵ㲢���������汻ɾ���Ľڵ㣬��ɾ������С�ڵ㡣
            while(temp->left != nullptr)
            {
                temp = temp->left;
            }
            // ������Ϣ
            r->name = temp->name;
            r->gender = temp->gender;
            r->num = temp->num;
            r->date = temp->date;
            r->salary = temp->salary;
            // ɾ����С�ڵ�
            deleteStaff(r->right,temp->num);
            return 1;
        }
    }
    return -1;
}
bool searchStaff(Staff *r, string num)
{
    /* if(r->num == num) {
         cout << "Ѱ�ҵ��Ĺ�Ա��Ϣ����:"<<endl;
         cout<<setw(10)<<left<<"����"<<setw(10)<<"�Ա�"<<setw(10)<<"�籣��"<<setw(10)<<"��������"<<setw(10)<<"н��"<<endl;
         cout<<setw(10)<<left<<r->name<<setw(10)<<r->gender<<setw(10)<<r->num<<setw(10)<<r->date<<setw(10)<<r->salary<<endl;
         return true;
     }
     if(num < r->num){
         if(r->left == nullptr)
         {
            return false;
         }
         else
         {
            return searchStaff(r->left,num);
         }
     } else{
         if(r->right == nullptr)
         {
            return false;
         }
         else
         {
            return searchStaff(r->right,num);
         }
     }*/
    // �ǵݹ�
    while(r != nullptr)
    {
        if(r->num == num)
        {
            cout << "Ѱ�ҵ��Ĺ�Ա��Ϣ����:"<<endl;
            cout<<setw(10)<<left<<"����"<<setw(10)<<"�Ա�"<<setw(10)<<"�籣��"<<setw(10)<<"��������"<<setw(10)<<"н��"<<endl;
            cout<<setw(10)<<left<<r->name<<setw(10)<<r->gender<<setw(10)<<r->num<<setw(10)<<r->date<<setw(10)<<r->salary<<endl;
            return true;
        }
        if(num < r->num)
        {
            r = r->left;
        }
        else
        {
            r = r->right;
        }
    }
    return false;
}
bool modifyStaff(Staff *&r, string num)    // ����ָ������ã���ָ��ı�����ֱ�Ӹı��Դ�ָ��Ϊ���ڵ�Ķ��������ɲ��÷���ֵ��
{
    if(r == nullptr)        // ������Ϊ��
    {
        return false;
    }
    if(num == r->num)
    {
        string temp;
        cout << "��ѡ��Ҫ�޸ĵ���Ŀ:" << endl;
        cout << "1.���� 2.�Ա� 3.�籣�� 4.�������� 5.н��" << endl;
        cin >> temp;
        cout << "������������" << endl;
        if(temp == "1")
        {
            cin >> r->name;
        }
        else if(temp == "2")
        {
            cin >> r->gender;
        }
        else if(temp == "3")
        {
            cin >> r->num;
        }
        else if(temp == "4")
        {
            cin >> r->date;
        }
        else if(temp == "5")
        {
            cin >> r->salary;
        }
        else
        {
            cout << "�޴�ѡ��" << endl;
        }
        cout << "�޸ĳɹ�!" << endl;
        return true;
    }
    if(num < r->num)
    {
        if(r->left == nullptr)
            return false;
        else
            return modifyStaff(r->left, num);
    }
    else
    {
        if(r->right == nullptr)
            return false;
        else
            return modifyStaff(r->right, num);
    }
}
int main()
{
    string option;
    Staff *R=nullptr;
    while(true)
    {
        cout << setw(20) << setfill('-') << '-' << endl;
        cout << "-----" << right << "1.�鿴ְԱ" << "-----" << endl;
        cout << "-----" << right << "2.���ְԱ" << "-----" << endl;
        cout << "-----" << right << "3.ɾ��ְԱ" << "-----" << endl;
        cout << "-----" << right << "4.����ְԱ" << "-----" << endl;
        cout << "-----" << right << "5.�޸�ְԱ" << "-----" << endl;
        cout << "-------" << right << "6.�˳�" << "-------" << endl;
        cout << setw(20) << setfill('-') << '-' <<endl;
        cout << "������ѡ��:" << endl;
        cin >> option;
        if(option == "1")
        {
            if(R->total != 0)
            {
                inOrderTraverse(R);
            }
            else
            {
                cout << "ĿǰְԱΪ��!" << endl;
            }
        }
        else if(option == "2")
        {
            string mes[5];
            cout << "������Ҫ��ӵ�ְԱ��Ϣ:" << endl;
            cout << "����\t�Ա�\t�籣��\t��������\tн��" << endl;
            cin >> mes[0];
            cin >> mes[1];
            cin >> mes[2];
            cin >> mes[3];
            cin >> mes[4];
            addStaff(&R, mes);
        }
        else if(option == "3")
        {
            string num;
            cout<<"������Ҫɾ����ְԱ�籣��:"<<endl;
            cin>>num;
            int res = deleteStaff(R,num);
            if(-1 == res)
            {
                cout<<"ְԱΪ��!"<<endl;
            }
            else if(0 == res)
            {
                cout<<"û�д��籣��...��ȷ��!"<<endl;
            }
            else
            {
                cout<<"ɾ���ɹ�!"<<endl;
            }
        }
        else if(option == "4")
        {
            bool flag = false;
            string num;
            cout << "������Ҫ���ҵ�ְԱ�籣��:" << endl;
            cin >> num;
            flag = searchStaff(R, num);
            if(!flag) cout << "����ʧ��!" << endl;
        }
        else if(option == "5")
        {
            bool flag = false;
            string num;
            cout << "������Ҫ�޸ĵ�ְԱ���籣��:" << endl;
            cin >> num;
            flag = modifyStaff(R, num);
            if(!flag) cout << "�޸�ʧ�ܣ�" << endl;
        }
        else if(option == "6")
        {
            cout << "bye bye!" << endl;
            break;
        }
        else
        {
            cout << "û�и�ѡ�" << endl;
        }
    }
    delete R;
    return 0;
}
/*
*summary: �Եݹ���ǵݹ����������һЩ�µļ���,�Զ�����������������˽⡣
*/
