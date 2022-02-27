#include <iostream>
using namespace std;
typedef long long ll;

//Global Declarations

struct node
{
    struct node *child[2];
    bool val;
};

struct tree_ptr
{
    struct node *child[2];
};

struct tree_ptr *create_tree()
{
    struct tree_ptr *ptr = new tree_ptr;
    int i{1};

    while (i > -1)
    {
        ptr->child[i] = NULL;
        i--;
    }

    return ptr;
}

struct node *create_node(bool val)
{
    struct node *ptr = new node;
    int i{1};

    while (i > -1)
    {
        ptr->child[i] = NULL;
        i--;
    }
    ptr->val = val;

    return ptr;
}

void insert(struct tree_ptr *root, ll val)
{
    int i{0}, j{63};
    bool rep[100];

    for (; i < 64; i++)
    {
        ll temp_res = val & 1;
        rep[j] = temp_res;

        val = val / 2;
        j--;
    }

    struct node *temp;

    bool check = root->child[rep[0]];
    if (check != true)
    {
        bool rep_val = rep[0];
        temp = create_node(rep_val);
        root->child[rep_val] = temp;
    }

    struct node *temp1;
    temp = root->child[rep[0]];
    i = 1;

    for (; i < 64; i++)
    {
        bool rep_val = rep[i];
        check = temp->child[rep_val];

        if (check != true)
        {
            temp1 = create_node(rep_val);
            temp->child[rep_val] = temp1;
        }
        temp = temp->child[rep_val];
    }
}

ll max_xor(struct tree_ptr *root, ll x)
{
    struct node *temp;
    bool xor_value[100];
    int i{0}, j{63};
    ll result = 0;

    for (; i < 64; i++)
    {
        ll temp_res = x & 1;
        xor_value[j] = temp_res;

        x = x / 2;
        j--;
    }

    bool value = !xor_value[0];
    bool check = root->child[value];

    if (check == true)
    {
        temp = root->child[value];
    }
    else
    {
        temp = root->child[!value];
    }

    result *= 2;
    result += temp->val;
    i = 1;

    for (; i < 64; i++)
    {
        bool value = !xor_value[i];
        bool check = temp->child[value];

        if (check == true)
        {
            temp = temp->child[value];
        }
        else
        {
            temp = temp->child[!value];
        }

        result *= 2;
        result += temp->val;
    }

    return result;
}

int main()
{
    ll N{1};
    cin >> N;

    ll numbers[N];
    struct tree_ptr *root = create_tree();

    for (ll i = 0; i < N; i++)
    {
        ll temp_num{0};
        cin >> temp_num;

        insert(root, temp_num);
        numbers[i] = temp_num;
    }

    ll q{0};
    cin >> q;
    ll queries[q];

    for (ll i = 0; i < q; i++)
    {
        ll x{0};
        cin >> x;

        queries[i] = x;
        ll temp_res = max_xor(root, x);
        ll result = temp_res ^ x;

        cout << result << "\n";
    }

    return 0;
}