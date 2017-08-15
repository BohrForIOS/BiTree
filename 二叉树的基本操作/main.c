//
//  main.c
//  二叉树的基本操作
//
//  Created by 王二 on 17/8/15.
//  Copyright © 2017年 mbs008. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
// 1.二叉树的定义
typedef int ElementType;

typedef struct BiTreeNode {
    ElementType data;
    struct BiTreeNode *lchild;
    struct BiTreeNode *rchild;
}BiTreeNode, *BiTree;

// 2.二叉树的建立和销毁
// 1.利用先序序列递归建立二叉树
void CreatePreBiTree(BiTree *T) {
    int data;
    scanf("%d", &data);
    
    if (data == 0) {
        *T = NULL;
        return;
    }
    else {
        *T = (BiTree)malloc(sizeof(BiTreeNode));
        if (T == NULL) {
            printf("分配空间失败\n");
            return ;
        }
        else {
            (*T)->data = data;
            printf("输入%d的左子节点：",data);
            CreatePreBiTree(&((*T)->lchild));
            printf("输入%d的右子节点：",data);
            CreatePreBiTree((&(*T)->rchild));
        }
    }
}

// 1.利用中序序列递归建立二叉树
void CreateMiddleBiTree(BiTree *T) {
    int data;
    scanf("%d", &data);
    
    if (data == 0) {
        *T = NULL;
        return;
    }
    else {
        *T = (BiTree)malloc(sizeof(BiTreeNode));
        if (T == NULL) {
            printf("分配空间失败\n");
            return ;
        }
        else {
            printf("输入%d的左子节点：",data);
            CreatePreBiTree(&((*T)->lchild));
            (*T)->data = data;
            printf("输入%d的右子节点：",data);
            CreatePreBiTree((&(*T)->rchild));
        }
    }
}

// 先序遍历二叉树
void PreOrderBiTree(BiTree T) {
    if (T == NULL) {
        return;
    }
    else {
        printf("data = %d", T->data);
        PreOrderBiTree(T->lchild);
        PreOrderBiTree(T->rchild);
    }
}
// 中序遍历二叉树
void MiddleOrderBiTree(BiTree T) {
    if (T == NULL) {
        return;
    }
    else {
        // 遍历左子树
        MiddleOrderBiTree(T->lchild);
        // 打印当前根结点
        printf("%d", T->data);
        // 遍历右子树
        MiddleOrderBiTree(T->rchild);
    }
}
// 后序遍历二叉树
void PostOrderBiTree(BiTree T) {
    if (T == NULL) {
        return;
    }
    else {
        // 遍历左子树
        PostOrderBiTree(T);
        // 打印当前结点
        printf("%d", T->data);
        // 遍历右子树
        PostOrderBiTree(T->rchild);
    }
}

// 获取二叉树的深度
int TreeDeep(BiTree T) {
    int deep = 0;
    if (T != NULL) {
        // 获取左子树深度
        int leftdeep = TreeDeep(T->lchild);
        int rightdeep = TreeDeep(T->rchild);
        
        deep = leftdeep >= rightdeep ? leftdeep + 1 : rightdeep + 1;
    }
    
    return deep;
}
// 获取叶子节点数
int LeafCount(BiTree T) {
    static int count = 0;
    
    if (T) {
        if (T->lchild == NULL && T->rchild == NULL) {
            count++;
        }
        
        LeafCount(T->lchild);
        LeafCount(T->rchild);
    }
    
    return count;
}

int main(int argc, const char * argv[]) {
    BiTree T = (BiTree)malloc(sizeof(BiTreeNode));
    CreateMiddleBiTree(&T);
    PreOrderBiTree(T);
    
    int leafCount = LeafCount(T);
    int treeDeep = TreeDeep(T);
    
    return 0;
}


#pragma mark - 线索二叉树

typedef enum {
    Link,
    Thread
} PointerTag;

typedef struct BiThrNode {
    int data;
    struct BiThrNode *lchild, *rchild;
    PointerTag ltag;
    PointerTag rtag;
}BiThrNode, *BiThrTree;

// 前序创建一颗二叉树
void CreatePreBiThrTree(BiThrTree T) {
    int data;
    scanf("%d", &data);
    
    if (data == 0) {
        T = NULL;
    }
    else {
        T = (BiThrTree)malloc(sizeof(BiThrNode));
        T->data = data;
        T->ltag = Link;
        T->rtag = Link;
        CreatePreBiThrTree(T->lchild);
        CreatePreBiThrTree(T->rchild);
    }
}

BiThrTree pre;

void MidddleInThreading(BiThrTree T) {
    if (T) {
        // 左孩子线索化
        if (T->lchild) {
           MidddleInThreading(T->lchild);
        }
        
        if (!T->lchild) {
            // 如果左孩子不存在
            T->lchild = pre;
        }
        
        // 右孩子线索化
        if (T->rchild) {
            MidddleInThreading(T->rchild);
        }
    }
}
