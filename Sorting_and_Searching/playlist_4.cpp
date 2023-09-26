#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

int l, r, maxLength, n;

// int longestUniqueSequence(const vector<int>& playlist) {
//     int n = playlist.size();
//     vector<int> uniqueSongs;
//     uniqueSongs.reserve(n);
//     int left = 0, right = 0;
//     int maxLength = 0;

//     while (right < n) {
//         int song = playlist[right];
//         auto it = find(uniqueSongs.begin(), uniqueSongs.end(), song);
//         if (it == uniqueSongs.end() || *it < left) {
//             uniqueSongs.push_back(song);
//             maxLength = max(maxLength, right - left + 1);
//             right++;
//         } else {
//             left = it - uniqueSongs.begin() + 1;
//             uniqueSongs.erase(uniqueSongs.begin(), it + 1);
//         }
//     }

//     return maxLength;
// }

int main() {
    l = r = maxLength = 0;
    cin >> n;

    vector<int> playlist(n);
    for (int i=0; i<n; i++) cin >> playlist[i];

    vector<int> uniqueSongs(n, -1);
    while (r < n) {
        int song = playlist[r];

        if (uniqueSongs[song] == -1 || uniqueSongs[song] < l) {
            uniqueSongs[song] = r;
            maxLength = max(maxLength, r - l + 1);
            r++;
        } else {
            l = uniqueSongs[song] + 1;
        }
    }

    cout << maxLength << '\n';
}