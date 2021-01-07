#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include<time.h>
#define MAX_LEVEL 6
const float P = 0.5;
using namespace std;

/// Skip list node
struct snode
{
    int value;
    snode **forw;
    snode(int level, int &value)
    {
        forw = new snode * [level + 1];
        memset(forw, 0, sizeof(snode*) * (level + 1));
        this->value = value;
    }
    ~snode()
    {
        delete [] forw;
    }
};

/// Skip list itself

struct skiplist
{
    snode *header;
    int value;
    int level;
    skiplist()
    {
        header = new snode(MAX_LEVEL, value);
        level = 0;
    }
    ~skiplist()
    {
        delete header;
    }
    void print_list();
    bool search_element(int &);
    void insert_element(int &);
};

/// Function to generate random value
float frand()
{
    return (float) rand() / RAND_MAX;
}

/// Function to generate random level number
int random_level()
{
    static bool first = true;
    if (first)
    {
        srand((unsigned)time(NULL));
        first = false;
    }
    int lvl = (int)(log(frand()) / log(1.-P));
    return lvl < MAX_LEVEL ? lvl : MAX_LEVEL;
}

/// Insert Function

void skiplist::insert_element(int &value)
{
    snode *x = header;
    snode *update[MAX_LEVEL + 1];
    memset(update, 0, sizeof(snode*) * (MAX_LEVEL + 1));
    for (int i = level;i >= 0;i--)
    {
        while (x->forw[i] != NULL && x->forw[i]->value < value)
        {
            x = x->forw[i];
        }
        update[i] = x;
    }
    x = x->forw[0];
    if (x == NULL || x->value != value)
    {
        int lvl = random_level();
        if (lvl > level)
        {
            for (int i = level + 1;i <= lvl;i++)
            {
                update[i] = header;
            }
            level = lvl;
        }
        x = new snode(lvl, value);
        for (int i = 0;i <= lvl;i++)
        {
            x->forw[i] = update[i]->forw[i];
            update[i]->forw[i] = x;
        }
    }
}

/// Search Function

bool skiplist::search_element(int &s_value)
{
    snode *x = header;
    for (int i = level;i >= 0;i--)
    {
        while (x->forw[i] != NULL && x->forw[i]->value < s_value)
        {
            x = x->forw[i];
        }
    }
    x = x->forw[0];
    return x != NULL && x->value == s_value;
}

/// Print Function
void skiplist::print_list()
{
    const snode *x = header->forw[0];
    while (x != NULL)
    {
        cout << x->value;
        x = x->forw[0];
        if (x != NULL)
            cout << " - ";
    }
    cout <<endl;
}
int main()
{
    skiplist skip_list_obj;
    int n = 6,x = 5,y = 8;

    //Insert elements in the skip list
    skip_list_obj.insert_element(n);
    skip_list_obj.insert_element(x);


    //Search for element in the skip list
    if(skip_list_obj.search_element(y))
        cout<<"Element "<<n<<" is in the list"<<endl;
    else
        cout<<"Element not found!"<<endl;


    //Print the skip list
    skip_list_obj.print_list();
    return 0;
}
