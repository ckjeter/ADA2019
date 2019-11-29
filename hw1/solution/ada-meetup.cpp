/* The algorithm is similar to counting inversion pairs via merge sort.  Notice
 * that the number of people in the range [l, r] equals the number of people
 * strictly smaller than r + 1 substracted by the number of people smaller than
 * l.  We can thus place the bounds and the preference factors into a single
 * array and operate on it. However, to avoid counting the bounds as people,
 * the flag `is_real_person` is set according to whether the value corresponds
 * to a person or a bound.
 */
#include <array>
#include <iostream>
#include <vector>

// Maximum possible N
constexpr int kN = 1'000'000;

// The element that we will be sorting. Corresponds to either a person or a
// upper/lower bound.
struct Element {
  int value, orig_idx;
  bool is_real_person, is_upper_bound;
  // Note that in case of identical values, the bounds needs to be placed
  // before the people so that the calculated answer indeed corresponds to the
  // number of people strictly smaller than the bound.
  bool operator<(const Element &rhs) const {
    return value != rhs.value ? value < rhs.value
                              : is_upper_bound > rhs.is_upper_bound;
  }
} buffer[kN * 3];

// D&C on vec[l .. r - 1] and place the results into ans.
void DivideAndConquer(int left, int right, std::vector<Element> &vec,
                      std::vector<std::array<int, 2>> &ans) {
  // Return on base case
  if (right - left <= 1) return;

  // Recursively operate on the left and right halves
  int mid = (left + right) / 2;
  DivideAndConquer(left, mid, vec, ans);
  DivideAndConquer(mid, right, vec, ans);

  int l = left, r = mid, idx = left, accumulator = 0;
  // While we still have work to do...
  while (l < mid || r < right) {
    // Which side should we take from?
    bool from_left = l < mid && (r >= right || vec[l] < vec[r]);
    buffer[idx] = from_left ? vec[l++] : vec[r++];
    if (from_left && buffer[idx].is_real_person) {
      // If we choose a person from the left, we increase the accumulator.
      ++accumulator;
    } else if (!from_left && !buffer[idx].is_real_person) {
      // If we choose a bound from the right, we update its answer.
      ans[buffer[idx].orig_idx][buffer[idx].is_upper_bound] += accumulator;
    }
    ++idx;
  }

  // Copy back from temporary buffer
  for (int i = left; i < right; i++) vec[i] = buffer[i];
}

int main() {
  // Read input
  std::cin.tie(nullptr), std::ios_base::sync_with_stdio(false);
  int n;
  std::cin >> n;
  std::vector<int> p(n), f(n);
  std::vector<Element> vec;
  vec.reserve(n * 3);
  for (int i = 0; i < n; i++) std::cin >> p[i];
  for (int i = 0; i < n; i++) std::cin >> f[i];

  // Push both the people and the bounds into the array
  for (int i = 0; i < n; i++) {
    vec.push_back({p[i] - f[i], i, false, false});
    vec.push_back({p[i] + f[i] + 1, i, false, true});
    vec.push_back({p[i], i, true, false});
  }

  // The answers are placed here.
  // ans_arr[i][0] denotes the number of people smaller than p[i] - f[i]
  // ans_arr[i][1] denotes the number of people smaller than p[i] + f[i] + 1
  std::vector<std::array<int, 2>> ans_arr(n);

  DivideAndConquer(0, int(vec.size()), vec, ans_arr);

  // Calculate and output the final answer.
  int64_t ans = 0;
  for (int i = 0; i < n; i++) ans += ans_arr[i][1] - ans_arr[i][0];
  std::cout << ans << '\n';
}
