// 이진 트리의 노드 값 합을 계산하는 함수
int sumTree(TreeNode* root) {
    if (root == NULL) {
        return 0; // 빈 트리의 값 합은 0입니다.
    }

    // 현재 노드의 값과 왼쪽 서브트리, 오른쪽 서브트리의 값 합을 더합니다.
    return root->data + sumTree(root->left) + sumTree(root->right);
}