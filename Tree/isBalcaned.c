// 높이 계산 함수
int height(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

// 이진 트리가 균형 트리인지 검사하는 함수
int isBalanced(TreeNode* root) {
    if (root == NULL) {
        return 1; // 빈 트리는 균형 트리입니다.
    }

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    // 왼쪽 서브트리와 오른쪽 서브트리의 높이 차이가 1 이하이면 균형 트리입니다.
    if (abs(leftHeight - rightHeight) <= 1 && isBalanced(root->left) && isBalanced(root->right)) {
        return 1;
    }

    return 0; // 균형 트리가 아닙니다.
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 이진 트리의 노드 값 합을 계산하는 함수
int sumTree(TreeNode* root) {
    if (root == NULL) {
        return 0; // 빈 트리의 값 합은 0입니다.
    }

    // 현재 노드의 값과 왼쪽 서브트리, 오른쪽 서브트리의 값 합을 더합니다.
    return root->data + sumTree(root->left) + sumTree(root->right);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////

int countNodesWithOneChild(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    int leftCount = countNodesWithOneChild(root->left);
    int rightCount = countNodesWithOneChild(root->right);

    // 현재 노드가 자식 노드를 정확히 하나만 가지고 있는 경우
    if ((root->left != NULL && root->right == NULL) || (root->left == NULL && root->right != NULL)) {
        return 1 + leftCount + rightCount;
    }
    else {
        return leftCount + rightCount;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
