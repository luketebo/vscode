/***
 * 二叉排序树的查找 p232 3(3) 第七章
 * 已知二叉排序树采用二叉链表存储结构，根结点的指针为T,链接点的数据结构为（Lchild,data,rchild)
 * 其中lchild rchild 分别指向该结点左右孩子的指针，data域存放结点的数据信息，请写出递归算法，从小到大
 * 输出二叉排序树中所有数据值 >= x 的结点的数据，要求先找到第一个满足条件的节点后，在一次输出其他满足
 * 条件的结点
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
typedef char ElemType;
// 创建二叉树定义
typedef struct
{
    ElemType data;
    struct BiNode *lchild, *rchild;
} BiNode, *BiTree;
// 创建二叉树
void CreateBiTree(BiTree *T)
{
    char ch = NULL;
    scanf("%c", &ch);
    if (ch == "#")
    {
        *T = NULL;
    }
    else
    {
        T = (BiNode *)malloc(sizeof(BiNode));
        (*T)->data = ch;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
}
void func(char root){
    printf("%c ",root);
}
// 打印二叉树
void Print_BiTree(BiTree T){
    if(T != NULL ){
        func(T->data);
        Print_BiTree(T->lchild);
        Print_BiTree(T->rchild);
    }
}
// 遍历算法
void Traverse_Tree(){

}
int main(){
    BiTree T = NULL;
    CreateBiTree(&T);
    Print_BiTree(T);
    
}