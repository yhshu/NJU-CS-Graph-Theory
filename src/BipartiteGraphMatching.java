import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class BipartiteGraphMatching {

    static int set1Size;
    static int set2Size;
    static List<List<Integer>> adjList1 = new ArrayList<>();
    static List<List<Integer>> adjList2 = new ArrayList<>();
    static int ans = 0;
    static List<Integer> partner1 = new ArrayList<>();
    static List<Integer> partner2 = new ArrayList<>();
    static boolean[] vis;
    static int smallerSet = 0;

    public static void main(String[] args) {

        // input
        Scanner sc = new Scanner(System.in);
        set1Size = sc.nextInt();
        set2Size = sc.nextInt();
        for (int i = 0; i < set2Size; i++) {
            adjList2.add(new ArrayList<>());
        }

        for (int i = 0; i < set1Size; i++) {
            adjList1.add(new ArrayList<>());
            int degree = sc.nextInt();
            for (int j = 0; j < degree; j++) {
                int nei = sc.nextInt();
                adjList1.get(i).add(nei);
                adjList2.get(nei - 1).add(i + 1);
            }
        }

        // algorithm
        vis = new boolean[Integer.max(set1Size, set2Size)];
        for (int i = 0; i < set1Size; i++) {
            partner1.add(-1);
        }
        for (int i = 0; i < set2Size; i++) {
            partner2.add(-1);
        }

        if (set1Size > set2Size) {
            smallerSet = 1;
        }
        for (int i = 0; i < Integer.min(set1Size, set2Size); i++) {
            Arrays.fill(vis, false);
            if (smallerSet == 0) {
                if (partner1.get(i) == -1) {
                    ans += path(i);
                }
            } else {
                if (partner2.get(i) == -1) {
                    ans += path(i);
                }
            }
        }

        // output
        System.out.println(ans);
    }

    private static int path(int i) {
        if (smallerSet == 0) {
            for (int j = 0; j < set2Size; j++) {
                if (hasEdge(i, j) && !vis[j]) {
                    vis[j] = true;
                    if (partner2.get(j) == -1 || path(partner2.get(j)) != 0) {
                        partner1.set(i, j);
                        partner2.set(j, i);
                        return 1;
                    }
                }
            }
        } else {
            for (int j = 0; j < set1Size; j++) {
                if (hasEdge(i, j) && !vis[j]) {
                    vis[j] = true;
                    if (partner1.get(j) == -1 || path(partner1.get(j)) != 0) {
                        partner2.set(i, j);
                        partner1.set(j, i);
                        return 1;
                    }
                }
            }
        }
        return 0;
    }

    private static boolean hasEdge(int i, int j) {
        if (smallerSet == 0) {
            for (Integer nei : adjList1.get(i)) {
                if (j + 1 == nei) {
                    return true;
                }
            }
        } else {
            for (Integer nei : adjList2.get(i)) {
                if (j + 1 == nei) {
                    return true;
                }
            }
        }
        return false;
    }
}
