// ���� Ʈ���� ��� �� ���� ����ϴ� �Լ�
int sumTree(TreeNode* root) {
    if (root == NULL) {
        return 0; // �� Ʈ���� �� ���� 0�Դϴ�.
    }

    // ���� ����� ���� ���� ����Ʈ��, ������ ����Ʈ���� �� ���� ���մϴ�.
    return root->data + sumTree(root->left) + sumTree(root->right);
}