#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<fstream>
using namespace std;

struct node1;
struct node2;
class Queue;
class Linked_list;
class Binary_Search_Tree;

struct node1
{
    string data;
    struct node1 *link;
};

class Linked_list
{
        struct node1 *start=NULL, *ptr=NULL;
        int no=0;
    public:
        void create(string);
        void ins_beg(string);
        void ins_mid(string);
        void ins_end(string);
        void insert(string);
        //void del_beg();
        //void del_mid(string);
        //void del_end();
        int no_of_elts();
        //void search(string);
        void display();
        bool operator==(Linked_list& ll);
        //void sum();
        friend Binary_Search_Tree;
};

struct node2
{
    Linked_list ll;
    struct node2 *lchild, *rchild;
};

class Binary_Search_Tree
{
    private:
        struct node2 *root, *ptr;
        int no;
    public:
        Binary_Search_Tree(){root=ptr=NULL;no=0;}
        void create(Linked_list&);
        void insert(Linked_list&);
        bool search(Linked_list&);
        node2* return_root();
        int return_no();
        void inorder(struct node2*);
        void preorder(struct node2*);
        void postorder(struct node2*);
        int Compare_Trees(node2*, Binary_Search_Tree&,int&);
        int identicalTrees(struct node2*, struct node2*);
        void inorderTraversal(struct node2*, Queue*);
};

class Queue
{
    private:
        int front, rear, n;
        Linked_list **ll;                                       //Dynamic Allocation for the Array of Linked Lists
    public:
        Queue(int);
        bool isqempty();
        bool isqfull();
        void enqueue(Linked_list&);
        Linked_list dequeue();
        int no_of_elts();
        void display();

};

void Queue::display()
{
    for(int i=0;i<n;i++)
    {
        ll[i]->display();
    }
}

Queue::Queue(int no)
{
    ll = new Linked_list* [no];
    rear=0;
    front=0;
    n=no;
}

bool Queue::isqempty()
{
    return rear==front?true:false;
}

bool Queue::isqfull()
{
    return rear==n?true:false;
}

void Queue::enqueue(Linked_list& l)
{
    if(!isqfull())
    {
        ll[rear] = new Linked_list;
        ll[rear] = &l;
        rear++;
    }
}

Linked_list Queue::dequeue()
{
    if(!isqempty())
    {
        Linked_list l = *ll[front++];
        return l;
    }
}

int Queue::no_of_elts()
{
    return rear-front;
}

void Linked_list::create(string elt)
{
    struct node1 *n=new node1;
    n->data=elt;
    n->link=NULL;
    start=n;
    no++;
}

void Linked_list::insert(string elt)
{
    if(start==NULL)
        create(elt);
    else
    {
        ptr=start;
        while(ptr->link!=NULL)
        {
            ptr=ptr->link;
        }
        struct node1 *n=new node1;
        n->data=elt;
        n->link=NULL;
        ptr->link=n;
        no++;
    }
}


/*


void Linked_list::del_beg()
{
    ptr=start;
    start=start->link;
    delete ptr;
    no--;
    //cout<<"\nElement deleted at beginning!";
}

void Linked_list::del_mid(int item)
{
    struct node *temp=NULL;
    ptr=start;
    while(ptr!=NULL)
    {
        if(ptr->link==NULL)
        {
            break;
        }
        else if(ptr->link->data==item)
        {
            temp=ptr->link;
            ptr->link=ptr->link->link;
            no--;
           // cout<<"\nElement deleted at middle!";
            break;
        }
        else
            ptr=ptr->link;
    }
    if(ptr->link==NULL)
    {
       // cout<<"\nElement to delete in the middle is not available!";
    }
    delete temp;
}

void Linked_list::del_end()
{
    struct node *temp=NULL;
    ptr=start;
    while(ptr->link->link!=NULL)
    {
        ptr=ptr->link;
    }
    temp=ptr->link;
    ptr->link=NULL;
    delete temp;
    no--;
    //cout<<"\nElement deleted at end!";
}

void Linked_list::searchh(int a)
{
    int c=0;
    ptr=start;
    while(ptr!=NULL)
    {
        if(ptr->data==a)
        {
            c=1;
            cout<<"\nElement found!"<<endl;
            break;
        }
        else
            ptr=ptr->link;
    }
    if(c==0);
        cout<<"\nElement not found!"<<endl;
}


*/

int Linked_list::no_of_elts()
{
    return no;
}

void Linked_list::display()
{
    //cout<<"\n------ Contents ------\n\n";
    ptr=start;
    while(ptr!=NULL)
    {
        cout<<ptr->data<<" ";
        ptr=ptr->link;
    }
    cout<<endl;
}

bool Linked_list::operator==(Linked_list& ll)
{
    if(no==ll.no)                                   //Comparing the no of words in each Linked_list
    {
        ptr=start;
        ll.ptr=ll.start;
        while(ptr!=NULL)
        {
            if(ptr->data!=ll.ptr->data)
                return false;
            ptr=ptr->link;
            ll.ptr=ll.ptr->link;
        }
        return true;
    }
    else                                            //If No of words do not match, they are not same
        return false;
}

void Binary_Search_Tree::create(Linked_list& a)
{
    struct node2 *n = new node2;
    n->ll=a;
    n->lchild=NULL;
    n->rchild=NULL;
    root=n;
    //n->ll.display();
}

void Binary_Search_Tree::insert(Linked_list& a)
{
    no++;                                           //Incrementing no to store the no of nodes (or) the no of lines in the file
    struct node2 *par=NULL;
    ptr=root;
    while(ptr!=NULL)
    {
        if(ptr->ll.start->data[0] < a.start->data[0])
        {
            par=ptr;
            ptr=ptr->rchild;
        }
        else if(ptr->ll.start->data[0] >= a.start->data[0])
        {
            par=ptr;
            ptr=ptr->lchild;
        }

    }
    if(root==NULL)
    {
        create(a);
    }
    else if(par->ll.start->data[0] < a.start->data[0])
    {
        struct node2 *n = new node2;
        n->ll=a;
        n->lchild=NULL;
        n->rchild=NULL;
        par->rchild=n;
        //n->ll.display();
    }
    else if(par->ll.start->data[0] >= a.start->data[0])
    {
        struct node2 *n = new node2;
        n->ll=a;
        n->lchild=NULL;
        n->rchild=NULL;
        par->lchild=n;
        //n->ll.display();
    }

}


bool Binary_Search_Tree::search(Linked_list& a)
{
    ptr=root;
    while(ptr!=NULL)
    {
        if(ptr->ll.start->data[0] < a.start->data[0])
        {
            ptr=ptr->rchild;
        }
        else if(ptr->ll.start->data[0] >= a.start->data[0])
        {
            if(ptr->ll==a)
                return true;
            else
            ptr=ptr->lchild;
        }

    }
    if(ptr==NULL)
        return false;
}


//void Binary_Search_Tree::search(Linked_list& l)
//{
//    ptr=root;
//    while(ptr!=NULL)
//    {
//        int c=0;
//        l.ptr=start;
//        ptr->ll.ptr=start;
//        if(l.no==ptr->ll.no)
//        {
//            while(ll.ptr!=NULL)
//            {
//                if(ptr->ll.ptr->data!=l.ptr->data)
//                    break;
//                else
//                {
//                    c++;
//                    l.ptr=l.ptr->link;
//                    ptr->ll.ptr=ptr->ll.ptr->link;
//                }
//            }
//            if(c==l.no)
//                return true;
//            else
//
//        }
//        else
//            continue;
//    }
//}



node2* Binary_Search_Tree::return_root()
{
    return root;
}

void Binary_Search_Tree::inorder(struct node2 *T)
{
    if(T!=NULL)
    {
        inorder(T->lchild);
        T->ll.display();
        inorder(T->rchild);
    }
}

void Binary_Search_Tree::preorder(struct node2 *T)
{
    if(T!=NULL)
    {
        T->ll.display();
        preorder(T->lchild);
        preorder(T->rchild);
    }
}



void Binary_Search_Tree::postorder(struct node2 *T)
{
    if(T!=NULL)
    {
        postorder(T->lchild);
        postorder(T->rchild);
        T->ll.display();
    }
}

int Binary_Search_Tree::return_no()
{
    return no;
}


//void Binary_Search_Tree::inorderTraversal(struct node2* T, Queue* q)
//{
//    if(T!=NULL)
//    {
//        inorderTraversal(T->lchild,q);
//        q->enqueue(T->ll);
//        inorderTraversal(T->rchild,q);
//    }
//}
//

int Binary_Search_Tree::Compare_Trees(struct node2* T, Binary_Search_Tree& b, int& d)
{
    if(T!=NULL)
    {
        Compare_Trees(T->lchild, b, d);
        if(b.search(T->ll))
        {
            return ++d;
        }
        Compare_Trees(T->rchild, b, d);
    }
}



void Compare(Queue* q1, Queue* q2, string x, string y)
{
    int d=0;
    int n1=q1->no_of_elts(), n2=q2->no_of_elts();
    Linked_list a[n1];
    for(int i=0;i<n1;i++)
        a[i]=q1->dequeue();
    Linked_list b[n2];
    for(int i=0;i<n2;i++)
        b[i]=q2->dequeue();
    int c[n1]={0};
    for(int i=0;i<n1;i++)
    {
        for(int j=0;j<n2;j++)
        {
            //cout<<bool(a[i]==b[j])<<endl;
            if(a[i]==b[j])
                c[i]+=1;
            else
                ;
        }
        //a[i].display();
    }
    for(int i=0;i<n1;i++)
    {
        if(c[i]==0)
            d++;
        //cout<<c[i]<<" ";
    }
    //cout<<d<<endl;
    cout<<"\n"<<x<<" matches "<<((float(n1)-float(d))/float(n1))*100<<"% with "<<y<<" !"<<endl;
}


int Binary_Search_Tree::identicalTrees(node2* a, node2* b)
{
    static int c = 0;
    if (a == NULL && b == NULL)
        return 1;
    if (a != NULL && b != NULL)
    {
        return
        {
            identicalTrees(a->lchild, b->lchild) &&
            identicalTrees(a->rchild, b->rchild)
//            cout<<c<<endl;
//            return c;
        };
    }
    return 1;
}



int main()
{
    Binary_Search_Tree bst1, bst2;
    char n;
    string a,b;
    cout<<"\nEnter the Name of the First File : ";
    cin>>a;
    cout<<"\nEnter the Name of the Second File: ";
    cin>>b;
    ifstream filea(a);
    ifstream fileb(b);
    if(!filea || !fileb)
    {
        cout<<"\nError in Opening File!";
        exit(0);
    }
    system("cls");
    cout<<"\n---------------------------\n"<<endl;
    cout<<"Contents in "<<a<<" are: "<<endl;
    cout<<"\n---------------------------\n"<<endl;
    while(!filea.eof())
    {
        Linked_list ll;
        string line, word;
        getline(filea,line);
        for(auto x : line)
        {
            if(x==' ')
            {
                ll.insert(word);
                word="";
            }
            else
                word+=x;
        }
        ll.insert(word);
        ll.display();
        bst1.insert(ll);
    }
    getch();
    system("cls");
    cout<<"\n---------------------------\n"<<endl;
    cout<<"Contents in "<<b<<" are: "<<endl;
    cout<<"\n---------------------------\n"<<endl;
    while(!fileb.eof())
    {
        Linked_list ll;
        string line, word;
        getline(fileb,line);
        for(auto x : line)
        {
            if(x==' ')
            {
                ll.insert(word);
                word="";
            }
            else
                word+=x;
        }
        ll.insert(word);
        ll.display();
        bst2.insert(ll);
    }
    getch();
    system("cls");
    cout<<"\nDo You want to Run a Plagiarism Check for "<<a<<" and "<<b<<" ?(y or n)"<<endl;
    cin>>n;
    //bst1.preorder(bst1.return_root());
    //bst2.preorder(bst2.return_root());
//    if(bst1.identicalTrees(bst1.return_root(),bst2.return_root()))
//        cout<<"\nBoth the Files are Similar!"<<endl;
//    else
//        cout<<"\nBoth the Files are not Similar!"<<endl;
    system("cls");
    if(n=='y')
    {
//        Queue q1(bst1.return_no());
//        Queue q2(bst2.return_no());
//        //cout<<q1.no_of_elts()<<endl<<q2.no_of_elts()<<endl;
//        bst1.inorderTraversal(bst1.return_root(),&q1);
//        bst2.inorderTraversal(bst2.return_root(),&q2);
//        Compare(&q1, &q2, a, b);
        int c=0;
        bst1.Compare_Trees(bst1.return_root(), bst2, c);
        cout<<"\n"<<a<<" matches "<<(float(c)/float(bst1.return_no()))*100<<" % with "<<b<<" !"<<endl;
    }
    else
    {
        cout<<"\nHave a Nice Day!"<<endl;
    }
}
