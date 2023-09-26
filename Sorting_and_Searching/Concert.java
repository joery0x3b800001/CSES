import java.util.*;

class Concert {
	static private int[] getUserPrices(int[] prices, int[] bids) {
		TreeMap<Integer, Integer> tree = new TreeMap<>();
		for (int price : prices) {
			if (tree.containsKey(price)) {
				tree.put(price, tree.get(price) + 1);
			} else {
				tree.put(price, 1);
			}
		}

		int[] result = new int[bids.length];
		for (int i = 0; i < bids.length; i++) {
			Integer k = tree.floorKey(bids[i]);
			if (k != null) {
				result[i] = k;
				int value = tree.get(k);
				if (value - 1 > 0) {
					tree.put(k, value - 1);
				} else {
					tree.remove(k);
				}
			} else {
				result[i] = -1;
			}
		}
		return result;
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int w = sc.nextInt();

		int[] prices = new int[n];
		int[] bids = new int[w];

		for (int i = 0; i < n; i++) prices[i] = sc.nextInt();
		for (int i = 0; i < w; i++) bids[i] = sc.nextInt();

		for (int x : getUserPrices(prices, bids)) {
			System.out.println(x);
		}
	}
}