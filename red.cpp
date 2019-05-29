
// Реализация red-black tree

#define COLOR_RED 0       // читает как 0
#define COLOR_BLACK 1

#include <cstddef>  // для std
#include <iostream>  
#include <cstdlib>

using namespace std;

struct rbtree 
{
// поля структуры
int key;
char *value; // указатель на первый элемент чаровского масссива
int color;

struct rbtree *parent;
struct rbtree *left;
struct rbtree *right;
};

struct rbtree EmptyNode = {0, 0, COLOR_BLACK, NULL, NULL, NULL}; // нулевая структура листьев

struct rbtree *NullNode = &EmptyNode;

void Free(rbtree *&root) // удалить дерево
{
    if (root->left)
        Free(root->left);
    if (root->right)
        Free(root->right);
#ifdef FL                // 
    Free ( root );
#else
    delete root;
#endif
    root = NULL;
}

void print_Tree(rbtree * p,int level) // печать дерева // p указатель на структуру (корня)
{
    if(p)
    {
        print_Tree(p->left,level + 1);
        for(int i = 0;i< level;i++) cout<<"   ";
        
        if(p->color)
        {
        	cout << "black" << p->key << endl;
        }

        else
        {
        	cout << "red" << p->key << endl;
        }
        
        print_Tree(p->right,level + 1);
    }
}

// Правый поворот (right rotate)

struct rbtree *rbtree_right_rotate(struct rbtree *root, struct rbtree *node)
{

struct rbtree *left = node->left;
// Create node->left link 
node->left = left->right;

if (left->right != NullNode)
left->right->parent = node;

// Create left->parent link 
if (left != NullNode)
left->parent = node->parent;

if (node->parent != NullNode) 
{
if (node == node->parent->right)
node->parent->right = left;
else
node->parent->left = left;
} 

else 
{
root = left;
}

left->right = node;
if (node != NullNode)
node->parent = left;
return root;
}

// Левый поворот (left rotate)

struct rbtree *rbtree_left_rotate(struct rbtree *root, struct rbtree *node)
{
struct rbtree *right = node->right;
/* Create node->right link */
node->right = right->left;
if (right->left != NullNode)
right->left->parent = node;
/* Create right->parent link */
if (right != NullNode)
right->parent = node->parent;

if (node->parent != NullNode) 
{
if (node == node->parent->left)
node->parent->left = right;
else
node->parent->right = right;
} 

else 
{
root = right;
}

right->left = node;
if (node != NullNode)
node->parent = right;
return root;
}



// Восстановление свойств после добавления

struct rbtree *rbtree_fixup_add(struct rbtree *root,struct rbtree *node)
{
struct rbtree *uncle;
/* Current node is RED */
while (node != root && node->parent->color == COLOR_RED)
{

if (node->parent == node->parent->parent->left)
{
/* node in left tree of grandfather */
uncle = node->parent->parent->right;

if (uncle->color == COLOR_RED) 
{
/* Case 1 - uncle is RED */
node->parent->color = COLOR_BLACK;
uncle->color = COLOR_BLACK;
node->parent->parent->color = COLOR_RED;
node = node->parent->parent;
} 

else 
{
/* Cases 2 & 3 - uncle is BLACK */
if (node == node->parent->right) 
{
/* Reduce case 2 to case 3 */
node = node->parent;
root = rbtree_left_rotate(root,node);
}

/* Case 3 */
node->parent->color = COLOR_BLACK;
node->parent->parent->color =COLOR_RED;
root = rbtree_right_rotate(root,node->parent->parent);
}

} 

else 
{
/* Node in right tree of grandfather */
uncle = node->parent->parent->left;

if (uncle->color == COLOR_RED) 
{
/* Uncle is RED */
node->parent->color = COLOR_BLACK;
uncle->color = COLOR_BLACK;
node->parent->parent->color = COLOR_RED;
node = node->parent->parent;
} 

else 
{

/* Uncle is BLACK */
if (node == node->parent->left) 
{
node = node->parent;
root = rbtree_right_rotate(root,node);
}
node->parent->color = COLOR_BLACK;
node->parent->parent->color = COLOR_RED;
root = rbtree_left_rotate(root,node->parent->parent);
}
}
}

root->color = COLOR_BLACK;
return root;
}

// Добавление узла

struct rbtree *rbtree_add(struct rbtree *root,int key, char *value)
{
struct rbtree *node, *parent = NullNode;
/* Search leaf for new element */
for (node = root; node != NullNode && node != NULL; )
{
parent = node;
if (key < node->key)
node = node->left;
else if (key > node->key)
node = node->right;
else
return root;
}

// node = malloc(sizeof(*node));
node = (struct rbtree *)malloc(sizeof(struct rbtree));
if (node == NULL)
return NULL;
node->key = key;
node->value = value;
node->color = COLOR_RED;
node->parent = parent;
node->left = NullNode;
node->right = NullNode;

if (parent != NullNode) 
{
if (key < parent->key)
parent->left = node;
else
parent->right = node;
} 

else 
{
root = node;
}

return rbtree_fixup_add(root, node);
}


// Пример формирования дерева

int main(int argc, char **argv)
{

struct rbtree *tree = NULL;


tree = rbtree_add(tree, 10, "10");
tree = rbtree_add(tree, 5, "5");
tree = rbtree_add(tree, 3, "3");
tree = rbtree_add(tree, 11, "11");
tree = rbtree_add(tree, 12, "12");
tree = rbtree_add(tree, 6, "6");
tree = rbtree_add(tree, 8, "8");
tree = rbtree_add(tree, 9, "9");

print_Tree(tree, 5);
  Free(tree);

return 0;
}























































