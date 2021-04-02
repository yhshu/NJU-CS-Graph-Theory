import java.util.*;

public class BipartiteGraphMatching {
    static int set1Size;
    static int set2Size;
    static List<Set<Integer>> adjList = new ArrayList<>();
    static int ans = 0;
    static List<Integer> partner = new ArrayList<>();
    static boolean[] vis;

    public static void main(String[] args) {

        // input
        Scanner sc = new Scanner(System.in);
        set1Size = sc.nextInt();
        set2Size = sc.nextInt();

        for (int i = 0; i < set1Size; i++) {
            adjList.add(new HashSet<>());
            int degree = sc.nextInt();
            for (int j = 0; j < degree; j++) {
                adjList.get(i).add(sc.nextInt() - 1);
            }
        }

        // algorithm
        vis = new boolean[set2Size];
        for (int i = 0; i < set2Size; i++) {
            partner.add(-1);
        }

        for (int i = 0; i < set1Size; i++) {
            Arrays.fill(vis, false);
            ans += dfs(i);
        }

        // output
        System.out.print(ans);
    }

    private static int dfs(int i) {
        for (int j = 0; j < set2Size; j++) {
            if (hasEdge(i, j) && !vis[j]) {
                vis[j] = true;
                if (partner.get(j) == -1 || dfs(partner.get(j)) != 0) {
                    partner.set(j, i);
                    return 1;
                }
            }
        }
        return 0;
    }

    private static boolean hasEdge(int i, int j) {
        return adjList.get(i).contains(j);
    }
}
