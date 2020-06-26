/*
*positon:计算与算法导论 p182
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
void inOrderTraverse(Staff *r )      // 中序遍历BST
{   if(r == nullptr)
    {
        return;
    }

    /*if(r != nullptr) {          // 递归中序遍历BST
        inOrderTraverse(r->left);
        cout << r->name << "\t" << r->gender << "\t" << r->num << "\t" << r->date << "\t" << r->salary << endl;
        inOrderTraverse(r->right);
    }*/
    // 非递归
    /*
        将该树的所有左子树压栈，直到叶子结点，即也为根节点，此时开始输出根节点（叶子结点）数据并弹栈，接下来访问该根节点的右子树，如是往复。
    */
    stack<Staff*> s;
    Staff *p=r;
    while(p != nullptr || !s.empty())   // 非递归中序遍历BST
    {
        while(p != nullptr)
        {
            s.push(p);
            p = p->left;
        }
        if(!s.empty())
        {
            p = s.top();
            cout << p->name << "\t" << p->gender << "\t" << p->num << "\t" << p->date << "\t" << p->salary << endl; //此时为
            s.pop();
            p = p->right;
        }
    }
}
void addStaff(Staff **r, string m[])    // 传递指针的指针，可在任何地方修改指针指向的地址的内容而不用返回。
{
    /* if(nullptr == (*r))         // 递归实现
     {
         *r = new Staff(m[0], m[1], m[2], m[3], atoi(m[4].c_str()));
         cout << "添加职员成功！" << endl;
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
    /* 非递归实现插入节点，比较当前节点的键与加入的节点的键，直到找到一个小于当前节点键的节点且它的左子树为空。*/
    if(r == nullptr)
    {
        *r = new Staff(m[0], m[1], m[2], m[3], atoi(m[4].c_str()));
        cout<<"添加成功!"<<endl;
        return;
    }
    while(r != nullptr)
    {
        if(nullptr == (*r))
        {
            *r = new Staff(m[0], m[1], m[2], m[3], atoi(m[4].c_str()));
            cout<<"添加成功!"<<endl;
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
    if(nullptr == r)        // BST为空
    {
        return -1;
    }
    if(r->num > num)        // 搜索左子树
    {
        return deleteStaff(r->left,num);
    }
    else if(r->num < num)   // 搜索右子树
    {
        return deleteStaff(r->right,num);
    }
    else
    {
        if(r->left == nullptr || r->right == nullptr)       // 删除的节点只有左子树或右子树
        {
            r = (r->left != nullptr)?r->left:r->right;
            return 1;
        }
        else
        {
            Staff *temp = r->right;      // 从右子树找一个最小节点并用它来代替被删除的节点，再删除该最小节点。
            while(temp->left != nullptr)
            {
                temp = temp->left;
            }
            // 覆盖信息
            r->name = temp->name;
            r->gender = temp->gender;
            r->num = temp->num;
            r->date = temp->date;
            r->salary = temp->salary;
            // 删除最小节点
            deleteStaff(r->right,temp->num);
            return 1;
        }
    }
    return -1;
}
bool searchStaff(Staff *r, string num)
{
    /* if(r->num == num) {
         cout << "寻找到的雇员信息如下:"<<endl;
         cout<<setw(10)<<left<<"姓名"<<setw(10)<<"性别"<<setw(10)<<"社保号"<<setw(10)<<"雇用日期"<<setw(10)<<"薪资"<<endl;
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
    // 非递归
    while(r != nullptr)
    {
        if(r->num == num)
        {
            cout << "寻找到的雇员信息如下:"<<endl;
            cout<<setw(10)<<left<<"姓名"<<setw(10)<<"性别"<<setw(10)<<"社保号"<<setw(10)<<"雇用日期"<<setw(10)<<"薪资"<<endl;
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
bool modifyStaff(Staff *&r, string num)    // 传递指针的引用，即指针的别名，直接改变以此指针为根节点的二叉树，可不用返回值。
{
    if(r == nullptr)        // 二叉树为空
    {
        return false;
    }
    if(num == r->num)
    {
        string temp;
        cout << "请选择要修改的项目:" << endl;
        cout << "1.姓名 2.性别 3.社保号 4.雇用日期 5.薪资" << endl;
        cin >> temp;
        cout << "请输入新内容" << endl;
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
            cout << "无此选项" << endl;
        }
        cout << "修改成功!" << endl;
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
        cout << "-----" << right << "1.查看职员" << "-----" << endl;
        cout << "-----" << right << "2.添加职员" << "-----" << endl;
        cout << "-----" << right << "3.删除职员" << "-----" << endl;
        cout << "-----" << right << "4.查找职员" << "-----" << endl;
        cout << "-----" << right << "5.修改职员" << "-----" << endl;
        cout << "-------" << right << "6.退出" << "-------" << endl;
        cout << setw(20) << setfill('-') << '-' <<endl;
        cout << "请输入选项:" << endl;
        cin >> option;
        if(option == "1")
        {
            if(R->total != 0)
            {
                inOrderTraverse(R);
            }
            else
            {
                cout << "目前职员为零!" << endl;
            }
        }
        else if(option == "2")
        {
            string mes[5];
            cout << "请输入要添加的职员信息:" << endl;
            cout << "姓名\t性别\t社保号\t雇用日期\t薪资" << endl;
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
            cout<<"请输入要删除的职员社保号:"<<endl;
            cin>>num;
            int res = deleteStaff(R,num);
            if(-1 == res)
            {
                cout<<"职员为空!"<<endl;
            }
            else if(0 == res)
            {
                cout<<"没有此社保号...请确认!"<<endl;
            }
            else
            {
                cout<<"删除成功!"<<endl;
            }
        }
        else if(option == "4")
        {
            bool flag = false;
            string num;
            cout << "请输入要查找的职员社保号:" << endl;
            cin >> num;
            flag = searchStaff(R, num);
            if(!flag) cout << "查找失败!" << endl;
        }
        else if(option == "5")
        {
            bool flag = false;
            string num;
            cout << "请输入要修改的职员的社保号:" << endl;
            cin >> num;
            flag = modifyStaff(R, num);
            if(!flag) cout << "修改失败！" << endl;
        }
        else if(option == "6")
        {
            cout << "bye bye!" << endl;
            break;
        }
        else
        {
            cout << "没有该选项！" << endl;
        }
    }
    delete R;
    return 0;
}
/*
*summary: 对递归与非递归遍历树有了一些新的见解,对二叉树运作有了深刻了解。
*/
