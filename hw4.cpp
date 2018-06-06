#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <queue>
using namespace std;

//define node type in tree
struct Node
{
    int value;
    struct Node *left = NULL;
    struct Node *right = NULL;
};
typedef struct Node node;

//use to count a specific value 
//input:  n 
//output: 2^(n-1)-1
int power_sp(int n){
    int ans = 1;
    for(int i = 0; i < n-1; i++)
        ans *= 2; 
    return --ans;
}

//save tree(linked list form) , total number in tree, level of tree in global  
node *head = NULL;
int number_node = 0;
int level_tree = 0;

void insertNode(node *current, int value)
{
    if (value < current->value)
    {
        if (current->left == NULL)
        {
            current->left = new node;
            current->left->value = value;
            return;
        }
        else
            insertNode(current->left, value);
    }
    else if (value > current->value)
    {
        if (current->right == NULL)
        {
            current->right = new node;
            current->right->value = value;
            return;
        }
        else
            insertNode(current->right, value);
    }
    else //value == currrent->value
        return;
};

int getLevel(node *cur_node)
{
    if (cur_node == NULL)
        return 0;
    else
    {
        //compare with level between left child and right child and return the bigger one
        //if the same, then return left(right will also work , but I choose left here)
        //return plus one for level increase
        if (getLevel(cur_node->left) >= getLevel(cur_node->right))
            return getLevel(cur_node->left) + 1;
        else if (getLevel(cur_node->left) < getLevel(cur_node->right))
            return getLevel(cur_node->right) + 1;
        else
        {
            cout << "getLevel() error" << endl;
            exit(1);
        }
    }
}

void drawTree(node *current){
    
};

//print out data in preorder form
void preorder(node *current)
{
    if (current == NULL)
        return;
    cout << current->value << " ";
    preorder(current->left);
    preorder(current->right);
};

//print out data in inorder form
void inorder(node *current)
{
    if (current == NULL)
        return;
    inorder(current->left);
    cout << current->value << " ";
    inorder(current->right);
};

//print out data in postorder form
void postorder(node *current)
{
    if (current == NULL)
        return;
    postorder(current->left);
    postorder(current->right);
    cout << current->value << " ";
};

//print out the triversal sequence in breath first search
void bfs(node *current)
{
    queue<node *> bfs_q;
    bfs_q.push(head);

    while (!bfs_q.empty())
    {
        if (bfs_q.front()->left != NULL)
            bfs_q.push(bfs_q.front()->left);
        if (bfs_q.front()->right != NULL)
            bfs_q.push(bfs_q.front()->right);
        cout << bfs_q.front()->value << " ";
        bfs_q.pop();
    }
};

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    //clear terminal first
    if (system("CLS"))
        system("clear");

    int input_mode;
    cout << "please choose data from: (1,2)" << endl;
    cin >> input_mode;

    //get input data from "data.txt"
    if (input_mode == 1)
    {
        ifstream fin;
        fin.open("data.txt", ifstream::in);
        if (!fin)
            return 1;
        head = new node;
        head->value = fin.get();
        while (fin.peek() != EOF)
        {
            insertNode(head, fin.get());
            number_node++;
        }
        fin.close();
    }
    //get input Data from random generater
    else if (input_mode == 2)
    {
        cout << "Data from random generater" << endl
             << "please input how many node to generate from rand(): (1 ~ 99)" << endl;
        cin >> number_node;
        if (number_node > 99 || number_node < 1)
        {
            cout << "input node number error, please input int number from 1 to 99" << endl;
            return 1;
        }

        //generate random number add build a tree
        head = new node;
        head->value = rand() % 100 + 1;
        for (int i = 1; i < number_node; i++)
            insertNode(head, rand() % 100 + 1);
    }
    else
    {
        cout << "input mode error, please input 1 or 2 next time" << endl;
        return 1;
    }

    //count the level of the tree
    level_tree = getLevel(head)
    //print out answer
    cout << "Level:     " << level_tree ;
    cout << endl
         << "Preorder:  ";
    preorder(head);
    cout << endl
         << "Inorder:   ";
    inorder(head);
    cout << endl
         << "Postorder: ";
    postorder(head);
    cout << endl
         << "BFS:       ";
    bfs(head);
    cout << endl;

    system("pause");
    return 0;
}