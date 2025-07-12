#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int key;
    struct node *left,*right;
}node;

node* create(node *root,int val){
    if((root)==NULL){
        (root)=(node*)malloc(sizeof(node));
        (root)->key=val;
        (root)->left=NULL;
        (root)->right=NULL;
        return root;
    }
    else{
        node* check=(root);
        if(check->key>val){
            root->left=create(root->left,val);
        }
        else{
            root->right=create(root->right,val);
        }
    }
    return root;
}

void preorder(node* root){
    if(root==NULL){
        return;
    }
    node* stack[100];
    int top=-1;
    stack[++top]=root;
    while(top>=0){
        node* current=stack[top--];
        printf("%d ",current->key);
        if(current->right){
            stack[++top]=current->right;
        }
        if(current->left){
            stack[++top]=current->left;
        }
    }
}
void inorder(node* root) {
    if (root == NULL) {
        return;
    }

    node* stack[100];
    int top = -1;
    node* current = root;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top--];
        printf("%d ", current->key);

        current = current->right;
    }
}
void postorder(node* root) {
    if (root == NULL) {
        return;
    }

    node* stack1[100];
    node* stack2[100];
    int top1 = -1;
    int top2 = -1;

    stack1[++top1] = root;

    while (top1 != -1) {
        node* current = stack1[top1--];
        stack2[++top2] = current;

        if (current->left) {
            stack1[++top1] = current->left;
        }

        if (current->right) {
            stack1[++top1] = current->right;
        }
    }

    while (top2 != -1) {
        printf("%d ", stack2[top2--]->key);
    }
}
int main(){
    node* root=NULL;
    int n;
    printf("enter a key\n");
    while(n!=-1){
        scanf("%d",&n);
        if(n!=-1){
            root=create(root,n);
        }
    }
    printf("check1");
    inorder(root);
}