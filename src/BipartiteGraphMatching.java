import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class BipartiteGraphMatching {

    public static void main(String[] args) {
        int set1Size;
        int set2Size;
        List<List<Integer>> adjList1 = new ArrayList<>();
        List<List<Integer>> adjList2 = new ArrayList<>();
        int ans = 0;

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


        // output
        System.out.print(ans);
    }
}
