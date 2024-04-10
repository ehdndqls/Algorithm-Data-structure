// ���� ��� �Լ�
int height(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

// ���� Ʈ���� ���� Ʈ������ �˻��ϴ� �Լ�
int isBalanced(TreeNode* root) {
    if (root == NULL) {
        return 1; // �� Ʈ���� ���� Ʈ���Դϴ�.
    }

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    // ���� ����Ʈ���� ������ ����Ʈ���� ���� ���̰� 1 �����̸� ���� Ʈ���Դϴ�.
    if (abs(leftHeight - rightHeight) <= 1 && isBalanced(root->left) && isBalanced(root->right)) {
        return 1;
    }

    return 0; // ���� Ʈ���� �ƴմϴ�.
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� Ʈ���� ��� �� ���� ����ϴ� �Լ�
int sumTree(TreeNode* root) {
    if (root == NULL) {
        return 0; // �� Ʈ���� �� ���� 0�Դϴ�.
    }

    // ���� ����� ���� ���� ����Ʈ��, ������ ����Ʈ���� �� ���� ���մϴ�.
    return root->data + sumTree(root->left) + sumTree(root->right);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////

int countNodesWithOneChild(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    int leftCount = countNodesWithOneChild(root->left);
    int rightCount = countNodesWithOneChild(root->right);

    // ���� ��尡 �ڽ� ��带 ��Ȯ�� �ϳ��� ������ �ִ� ���
    if ((root->left != NULL && root->right == NULL) || (root->left == NULL && root->right != NULL)) {
        return 1 + leftCount + rightCount;
    }
    else {
        return leftCount + rightCount;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
