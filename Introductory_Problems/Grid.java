import java.util.*;
import java.io.*;

class Reader {
    static BufferedReader reader;
    static StringTokenizer tokenizer;

    /** call this method to initialize reader for InputStream */
    static void init(InputStream input) {
        reader = new BufferedReader(
                     new InputStreamReader(input) );
        tokenizer = new StringTokenizer("");
    }

    /** get next word */
    static String next() throws IOException {
        while ( ! tokenizer.hasMoreTokens() ) {
            //TODO add check for eof if necessary
            tokenizer = new StringTokenizer(
                   reader.readLine() );
        }
        return tokenizer.nextToken();
    }

    static int nextInt() throws IOException {
        return Integer.parseInt( next() );
    }
	
    static double nextDouble() throws IOException {
        return Double.parseDouble( next() );
    }
}

    // Reader.init( System.in ); // connect Reader to an input stream
    //  double x = Reader.nextDouble();
    //  int n = Reader.nextInt();

class Grid {
	// final int DIR_LEN = 4;
	static int dr[] = {-1,0,1,0};
	static int dc[] = {0,1,0,-1};
	static final int PATH_LEN = 48;
	static int[] p = new int[PATH_LEN];
	static final int GRID_SIZE = 9;
	static boolean[][] onPath = new boolean[GRID_SIZE][GRID_SIZE];

	static int calculatePath(int pathIdx, int curR, int curC) {
		if ((onPath[curR][curC - 1] && onPath[curR][curC + 1])
			&& (!onPath[curR - 1][curC] && !onPath[curR + 1][curC])) return 0;

		if ((onPath[curR - 1][curC] && onPath[curR + 1][curC])
				&& (!onPath[curR][curC - 1] && !onPath[curR][curC + 1])) return 0;

		if (curR == 7 && curC == 1) {
			if (pathIdx == PATH_LEN) return 1;
			return 0;
		}

		if (pathIdx == PATH_LEN) return  0;

		int ret = 0;
		onPath[curR][curC] = true;

		if (p[pathIdx] < 4) {
			int nxtR = curR + dr[p[pathIdx]];
			int nxtC = curC + dc[p[pathIdx]];
			if (!onPath[nxtR][nxtC]) {
				ret += calculatePath(pathIdx + 1, nxtR, nxtC);
			}
		}
		else if ((curC > 2) && onPath[curR][curC-2]
					&& (onPath[curR-1][curC-1] || onPath[curR+1][curC+1])
					&& (!onPath[curR][curC-1]))
		{
			int nxtR = curR;
			int nxtC = curC-1;
			ret += calculatePath(pathIdx + 1, nxtR, nxtC);
		}
		else if ((curR > 2) && onPath[curR-2][curC] && onPath[curR-1][curC-1]
					&& (onPath[curR-1][curC+1] || onPath[curR+1][curC+1])
					&& (!onPath[curR][curC+1]))
		{
			int nxtR = curR;
			int nxtC = curC+1;
			ret += calculatePath(pathIdx + 1, nxtR, nxtC);

		}
		else if((curR > 2) && onPath[curR-2][curC] && onPath[curR-1][curC]
					&& (!onPath[curR-1][curC]))
		{
			int nxtR = curR-1;
			int nxtC = curC;
			ret += calculatePath(pathIdx + 1, nxtR, nxtC);
		}
		else {
			for (int i = 0; i < 4; i++) {
				int nxtR = curR + dr[i];
				int nxtC = curC + dc[i];
				if (onPath[nxtR][nxtC]) continue;
				ret += calculatePath(pathIdx + 1, nxtR, nxtC);
			}
		}
		onPath[curR][curC] = false;
		return ret;
	}

	public static void main(String[] args) {
		try {
			Scanner sc = new Scanner(System.in);
			String line = sc.nextLine();

			for (int i=0; i<PATH_LEN; i++) {
				char cur = line.charAt(i);

				if (cur == 'U') p[i] = 0;
				else if (cur == 'R') p[i] = 1;
				else if (cur == 'D') p[i] = 2;
				else if (cur == 'L') p[i] = 3;
				else p[i] = 4;
			}

			for (int i=0; i<GRID_SIZE; i++) {
				onPath[0][i] = true;
				onPath[8][i] = true;
				onPath[i][0] = true;
				onPath[i][8] = true;
			}

			for (int i=1; i<=7; i++) {
				for (int j=1; j<= 7; j++) {
					onPath[i][j] = false;
				}
			}

		
			int result = calculatePath(0, 1, 1);
			System.out.println(result);
		} catch(Exception e) {
			System.out.println(e.getMessage());
		}
	}
}