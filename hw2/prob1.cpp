/*
5 20 20 1537688804 584589912 3972715898 2166415565
10 20 20 4041108152 584535659 2466603739 198973427
*/
#include <array>
#include <iostream>
#include <random>
using namespace std;

namespace ada {

class Xoroshiro128 {
 public:
  using result_type = uint32_t;
  static constexpr result_type(min)() { return 0; }
  static constexpr result_type(max)() { return UINT32_MAX; }
  static inline result_type rotl(const result_type x, int k) {
    return (x << k) | (x >> (32 - k));
  }
  Xoroshiro128() : Xoroshiro128(1, 2, 3, 4) {}
  Xoroshiro128(result_type a, result_type b, result_type c, result_type d)
      : s{a, b, c, d} {}
  result_type operator()() {
    const result_type result = rotl(s[0] + s[3], 7) + s[0];
    const result_type t = s[1] << 9;
    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];
    s[2] ^= t;
    s[3] = rotl(s[3], 11);
    return result;
  }

 private:
  std::array<result_type, 4> s;
};

namespace {
int c_lead, c_team;
Xoroshiro128 rng;
}  // namespace

int Init() {
  int n;
  uint32_t s1, s2, s3, s4;
  std::cin >> n >> c_lead >> c_team >> s1 >> s2 >> s3 >> s4;
  rng = Xoroshiro128(s1, s2, s3, s4);
  return n;
}

int GetLeadership() { return uint64_t(rng()) * c_lead >> 32; }

int GetTeamValue() {
  int tmp = int(uint64_t(rng()) * c_team >> 32) + 1;
  return int(c_team / sqrt(tmp));
}

}  // namespace ada


const int kN = 2000000;
int mod = 1000000007;
int leadership[kN], team_value[kN];
long long dp[kN];
long long dpsum[kN];
long long teamsum[kN];

int searchmember(int left, int right, long long value){
//把teamsum[i]+leadership[i]做binary search插進(teamsum[i+1]~teamsum[n-1]),index - i就是membercount
    if (left > right) {
        return left;
    }
    int mid = left + (right - left) / 2;
    if (value < teamsum[mid])
    {
        return searchmember(left, mid - 1, value);
    }
    else
    {
        return searchmember(mid + 1, right, value);
    }
}
int main()
{
    int n = ada::Init(); // Get N
    for (int i = 0; i < n; i++) leadership[i] = ada::GetLeadership();
    for (int i = 0; i < n; i++) team_value[i] = ada::GetTeamValue();

    teamsum[0] = team_value[0];
    for (int i = 1; i < n; i++) {
        teamsum[i] = teamsum[i-1] + team_value[i] * 1ll;
    }

    dp[0] = 1;
    dp[1] = 1;
    dpsum[0] = 0;
    dpsum[1] = 1;
    dpsum[2] = 2;
    //dpsum[i] = dp[0] + .... + dp[i-1]
    //-> dp[i] = dpsum[]

    for (size_t i = 2; i <= n; i++) {
        int member_count = searchmember(n-i+1, n-1, teamsum[n-i] + leadership[n-i] * 1ll) - (n-i+1); //(left, right, value)
        dp[i] = dpsum[i] - dpsum[i - 1 - member_count];
        dpsum[i + 1] = dpsum[i] + dp[i] % mod;
    }
    printf("%lld\n", dp[n] % mod);
}
