#include<stdio.h>
#include<stdlib.h>
struct node{
    int info;
    struct node* left;
    struct node* right;
};
struct node* head=NULL;
struct node* createnode(int data);
struct node* find(struct node* root,int data);
struct node* insert(struct node* root,int data);
struct node* delete(struct node* root,int data);
int findmin(struct node* root);
int findmax(struct node* root);
void preorder(struct node* root);
void inorder(struct node* root);
void postorder(struct node* root);

int main(){
    
    head=insert(head,23);
    head=insert(head,56);
    head=insert(head,88);
    head=insert(head,3);
    head=insert(head,90);
    printf("%d\t%d\n",findmax(head),findmin(head));
    preorder(head);
    printf("\n");
    inorder(head);
    printf("\n");
    postorder(head);
    printf("\n");
    head=delete(head,88);
    inorder(head);

    return 0;
}
struct node* createnode(int data){
    struct node* ptr=malloc(sizeof(struct node));
    ptr->info=data;
    ptr->left=ptr->right=NULL;
    return ptr;
}
struct node* find(struct node* root,int data){
    if(root->info==data || root==NULL){
        //if element found or... we reached the end of tree
        return root;
    }
    else if(data>root->info){
        return find(root->right,data);
    }
    else{
        return find(root->left,data);
    }
}
struct node* insert(struct node* root,int data){
    if(root==NULL){
        root=createnode(data);
    }
    else{
        if(data>root->info){
            root->right=insert(root->right,data);
        }
        else{
            root->left=insert(root->left,data);
        }
    }
    return root;
}

struct node* delete(struct node* root,int data){
    if(root==NULL){
        return root;
    }
    //find the position of the node
    if(data>root->info){
        root->right=delete(root->right,data);
    }
    else if(data<root->info){
        root->left=delete(root->left,data);
    }
    //node found then check what type of node it is
    else{
        //no children or one child both cases can be handled by following code
        if(root->left==NULL ){
            //point to its child
            struct node* temp=root->right;
            free(root);
            //attatch child to the parent of deleted node
            return temp;
        }
        else if( root->right==NULL){
            struct node* temp=root->left;
            free(root);
            return temp;
        }
        //with two cildren copy inorder successor into current node and call delete function for
        //inorder successor on right subtree of current node
        struct node* temp=root->right;
        while(temp->left!=NULL){
            temp=temp->left;
        }
        root->info=temp->info;
        root->right=delete(root->right,temp->info);
    }
    return root;

}
int findmin(struct node* root){
    struct node* ptr=root;
    while(ptr->left!=NULL){
        ptr=ptr->left;
    }
    return ptr->info;
}
int findmax(struct node* root){
    struct node* ptr=root;
    while(ptr->right!=NULL){
        ptr=ptr->right;
    }
    return ptr->info;
}
void preorder(struct node* root){
    if(root){
        printf("%d---->",root->info);
        preorder(root->left);
        preorder(root->right);
    }
}
void postorder(struct node* root){
    if(root){
        postorder(root->left);
        postorder(root->right);
        printf("%d---->",root->info);
    }
}
void inorder(struct node* root){
    if(root){
        inorder(root->left);
        printf("%d---->",root->info);
        inorder(root->right);
    }
}