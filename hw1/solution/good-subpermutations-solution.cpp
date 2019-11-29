#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

constexpr int kN = 500000;

int64_t DivideConquer(const std::vector<int> &a, int l, int r) {
  if (r - l == 1) return 1;
  int m = (l + r) >> 1;
  int64_t res = DivideConquer(a, l, m) + DivideConquer(a, m, r);
  static std::array<int, 2 * kN + 10> cnt{};
  for (int i = m - 1, j = m, k = m, x = 0, y = kN, z = kN, w = kN; i >= l;
       --i) {               // the maximum is in [l, m)
    x = std::max(x, a[i]);  // x = max(a[i], a[i + 1], ..., a[m - 1])
    z = std::min(z, a[i]);  // z = min(a[i], a[i + 1], ..., a[m - 1])
    while (j < r && a[j] < x) {
      y = std::min(y, a[j]);  // y = min(a[m], a[m + 1], ..., a[j])
      ++cnt[y + j];
      ++j;
    }
    while (k < j && std::min(w, a[k]) > z) {
      w = std::min(w, a[k]);  // w = min(a[m], a[m + 1], ..., a[k])
      --cnt[w + k];
      ++k;
    }
    // cnt[x + i]: minimum in [m, r)
    // x - z + i: minimum in [l, m)
    res += cnt[x + i] + (x - z + i >= m && x - z + i < k);
  }
  for (int j = m, z = kN; j < r; ++j) {
    z = std::min(z, a[j]);
    cnt[z + j] = 0;
  }
  for (int i = m, j = m - 1, k = m - 1, x = 0, y = kN, z = kN, w = kN; i < r;
       ++i) {               // the maximum is in [m, r)
    x = std::max(x, a[i]);  // x = max(a[m], a[m + 1], ..., a[i])
    z = std::min(z, a[i]);  // z = min(a[m], a[m + 1], ..., a[i])
    while (j >= l && a[j] < x) {
      y = std::min(y, a[j]);  // y = min(a[j], a[j + 1], ..., a[m - 1])
      ++cnt[y - j + kN];
      --j;
    }
    while (k > j && std::min(w, a[k]) > z) {
      w = std::min(w, a[k]);  // w = min(a[k], a[k + 1], ..., a[m - 1])
      --cnt[w - k + kN];
      --k;
    }
    // cnt[x - i]: minimum in [l, m), increment the indices by kN to avoid
    // accessing negative indices.
    // i - x + z: minimum in [m, r)
    res += cnt[x - i + kN] + (i - x + z > k && i - x + z < m);
  }
  for (int j = m - 1, z = kN; j >= l; --j) {
    z = std::min(z, a[j]);
    cnt[z - j + kN] = 0;
  }
  return res;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) std::cin >> a[i];
  std::cout << DivideConquer(a, 0, n) << std::endl;
  return 0;
}
