#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Loi cap phat bo nho!\n");
        return NULL;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insertBST(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insertBST(root->left, data);
    } else if (data > root->data) {
        root->right = insertBST(root->right, data);
    }
    return root;
}

  void printTreeASCII(Node* root, char* prefix, int isLast) {
      if (root == NULL) return;
      printf("%s", prefix);
      printf("+- ");
      if (root->data < 0) {
          printf("(%d)\n", root->data);
      } else {
          printf("%d\n", root->data);
      }
      char newPrefix[1000];
      strcpy(newPrefix, prefix);
      strcat(newPrefix, isLast ? "   " : "|  ");
      int hasLeft = (root->left != NULL);
      int hasRight = (root->right != NULL);
      if (hasLeft) {
          printTreeASCII(root->left, newPrefix, !hasRight);
      }
      if (hasRight) {
          printTreeASCII(root->right, newPrefix, 1);
      }
  }

void drawTree(Node* root) {
    if (root == NULL) {
        printf("Cay rong!\n");
        return;
    }
    if (root->data < 0) {
        printf("(%d)\n", root->data);
    } else {
        printf("%d\n", root->data);
    }
    int hasLeft = (root->left != NULL);
    int hasRight = (root->right != NULL);
    if (hasLeft) {
        printTreeASCII(root->left, "", !hasRight);
    }
    if (hasRight) {
        printTreeASCII(root->right, "", 1);
    }
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void duyetNLR(Node* root) {
    if (root == NULL) return;
    if (root->data < 0) {
        printf("(%d) ", root->data);
    } else {
        printf("%d ", root->data);
    }
    duyetNLR(root->left);
    duyetNLR(root->right);
}

void duyetLNR(Node* root) {
    if (root == NULL) return;
    duyetLNR(root->left);
    if (root->data < 0) {
        printf("(%d) ", root->data);
    } else {
        printf("%d ", root->data);
    }
    duyetLNR(root->right);
}

void duyetLRN(Node* root) {
    if (root == NULL) return;
    duyetLRN(root->left);
    duyetLRN(root->right);
    if (root->data < 0) {
        printf("(%d) ", root->data);
    } else {
        printf("%d ", root->data);
    }
}

Node* searchBST(Node* root, int x) {
    if (root == NULL) return NULL;
    if (root->data == x) return root;
    if (x < root->data) return searchBST(root->left, x);
    return searchBST(root->right, x);
}

Node* deleteNode(Node* root, int x) {
    if (root == NULL) return NULL;
    if (x < root->data) {
        root->left = deleteNode(root->left, x);
    } else if (x > root->data) {
        root->right = deleteNode(root->right, x);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        } else {
            Node* temp = root->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}

int treeHeight(Node* root) {
    if (root == NULL) return 0;
    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int countNodes(Node* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int main() {
    Node* root = NULL;
    int choice;
    do {
        printf("1. Nhap du lieu tao cay BST\n");
        printf("2. Them 1 phan tu vao cay hien co\n");
        printf("3. Duyet NLR\n");
        printf("4. Duyet LNR\n");
        printf("5. Duyet LRN\n");
        printf("6. Tim kiem phan tu trong cay\n");
        printf("7. Xoa node\n");
        printf("8. Ve cay BST\n");
        printf("9. Tinh chieu cao & dem so node\n");
        printf("10. Xoa cay va giai phong bo nho\n");
        printf("0. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                freeTree(root);
                root = NULL;
                int n, val;
                printf("Nhap so luong phan tu: ");
                scanf("%d", &n);
                printf("Nhap cac gia tri:\n");
                for (int i = 0; i < n; i++) {
                    scanf("%d", &val);
                    root = insertBST(root, val);
                }
                break;
            }
            case 2: {
                int val;
                printf("Nhap gia tri can them: ");
                scanf("%d", &val);
                root = insertBST(root, val);
                printf("Da them gia tri %d vao cay.\n", val);
                break;
            }
            case 3:
                printf("Duyet NLR: ");
                duyetNLR(root);
                printf("\n");
                break;
            case 4:
                printf("Duyet LNR: ");
                duyetLNR(root);
                printf("\n");
                break;
            case 5:
                printf("Duyet LRN: ");
                duyetLRN(root);
                printf("\n");
                break;
            case 6: {
                int x;
                printf("Nhap gia tri can tim: ");
                scanf("%d", &x);
                Node* found = searchBST(root, x);
                if (found) {
                    printf("Tim thay node co gia tri: %d, dia chi: %p\n", found->data, (void*)found);
                } else {
                    printf("Khong tim thay gia tri %d trong cay.\n", x);
                }
                break;
            }
            case 7: {
                int x;
                printf("Nhap gia tri can xoa: ");
                scanf("%d", &x);
                Node* found = searchBST(root, x);
                if (found) {
                    root = deleteNode(root, x);
                    printf("Da xoa node co gia tri: %d\n", x);
                } else {
                    printf("Khong tim thay node co gia tri: %d\n", x);
                }
                break;
            }
            case 8:
                drawTree(root);
                break;
            case 9: {
                int height = treeHeight(root);
                int count = countNodes(root);
                printf("Chieu cao cua cay: %d\n", height);
                printf("Tong so node: %d\n", count);
                break;
            }
            case 10:
                freeTree(root);
                root = NULL;
                printf("Da xoa cay va giai phong bo nho.\n");
                break;
            case 0:
                printf("Ket thuc chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 0);
    freeTree(root);
    return 0;
}
