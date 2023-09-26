#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main() {
	int street_len;
	int light_num;
	std::cin >> street_len >> light_num;
	vector<int> lights(light_num);
	for (int &l : lights) { std::cin >> l; }

	vector<std::pair<int, int>> sorted_lights(light_num);
	for (int l = 0; l < light_num; l++) { sorted_lights[l] = {lights[l], l}; }
	std::sort(sorted_lights.begin(), sorted_lights.end());

	// Given the light position, this array stores its position in
	// sorted_lights.
	vector<int> new_pos(light_num);
	for (int l = 0; l < light_num; l++) {
		new_pos[sorted_lights[l].second] = l;
	}

	struct Light {
		int prev, next;
		int pos;
	};
	vector<Light> light_ll(light_num + 2);
	// First, we set our "lights" on the edges of the street.
	light_ll[0] = {-1, 1, 0};
	light_ll[light_num + 1] = {light_num, -1, street_len};
	for (int l = 0; l < light_num; l++) {
		light_ll[l + 1] = {l, l + 2, sorted_lights[l].first};
	}

	// Find the longest passage once all the streetlights are added
	vector<int> gaps(light_num);
	int max_gap = 0;
	for (int l = 0; l <= light_num; l++) {
		max_gap = std::max(max_gap, light_ll[l + 1].pos - light_ll[l].pos);
	}
	gaps.back() = max_gap;

	// Remove the streetlights in reverse order like as we did in the above
	// solution.
	for (int l = light_num - 1; l > 0; l--) {
		Light to_del = light_ll[new_pos[l] + 1];
		Light &left = light_ll[to_del.prev];
		Light &right = light_ll[to_del.next];
		// Re-assign the references to the next & previous node
		left.next = to_del.next;
		right.prev = to_del.prev;

		max_gap = std::max(max_gap, right.pos - left.pos);
		gaps[l - 1] = max_gap;
	}

	for (int i = 0; i < gaps.size() - 1; i++) { cout << gaps[i] << ' '; }
	cout << gaps.back() << endl;
}