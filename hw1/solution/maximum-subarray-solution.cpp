#include <algorithm>
#include <iostream>
#include <vector>

struct TreeNode {
  TreeNode *lc, *rc, *fa;
  // lc = the left child, rc = the right child
  // fa = the parent

  int64_t sum, res, prefix, suffix;
  // sum = the sum of the segment.
  // res = the maximum subarray of the segment.
  // prefix = the maximum prefix sum of the segment.
  // suffix = the maximum suffix sum of the segment.

  TreeNode() = default;

  TreeNode(int64_t v)
      : lc(nullptr),
        rc(nullptr),
        fa(nullptr),
        sum(v),
        res(std::max(int64_t(0), v)),
        prefix(std::max(int64_t(0), v)),
        suffix(std::max(int64_t(0), v)) {}

  TreeNode(TreeNode *lp, TreeNode *rp) : lc(lp), rc(rp), fa(nullptr) { Pull(); }

  void Update(int64_t v) {
    sum = v;
    res = prefix = suffix = std::max(int64_t(0), v);
  }

  void Pull() {
    lc->fa = this;
    rc->fa = this;
    sum = lc->sum + rc->sum;
    prefix = std::max(lc->prefix, lc->sum + rc->prefix);
    suffix = std::max(rc->suffix, rc->sum + lc->suffix);
    res = std::max(lc->res, rc->res);
    res = std::max(res, lc->suffix + rc->prefix);
  }
};

TreeNode *DivideConquer(int l, int r, const std::vector<TreeNode *> &leaf) {
  if (r - l == 1) return leaf[l];
  int m = (l + r) >> 1;
  return new TreeNode(DivideConquer(l, m, leaf), DivideConquer(m, r, leaf));
}

void Update(int p, int64_t v, const std::vector<TreeNode *> &tree) {
  // update all ancestors of the modified node.
  TreeNode *ptr = tree[p];
  ptr->Update(v);
  while (ptr->fa) {  // ptr is not the root.
    ptr = ptr->fa;
    ptr->Pull();
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int n, q;
  std::cin >> n >> q;
  std::vector<TreeNode *> tree(n);  // leaf nodes, representing the segments of
                                    // length 1 on the original array.
  for (int i = 0; i < n; ++i) {
    int64_t v;
    std::cin >> v;
    tree[i] = new TreeNode(v);
  }

  TreeNode *root = DivideConquer(0, n, tree);
  std::cout << root->res << std::endl;

  while (q--) {
    int p;
    int64_t v;
    std::cin >> p >> v;
    --p;
    Update(p, v, tree);
    std::cout << root->res << std::endl;
  }
}
