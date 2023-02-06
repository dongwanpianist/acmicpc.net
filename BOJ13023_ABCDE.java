import java.util.Scanner;
import java.util.ArrayList;
@SuppressWarnings("unchecked")
public class BOJ13023_ABCDE {
    static ArrayList<Integer>[] mylist;
    static boolean fivebridges(int A){
        for (int B : mylist[A]) {
            for (int C : mylist[B]) {
                if (C==A) continue;
                for (int D : mylist[C]) {
                    if (D==A) continue;
                    if (D==B) continue;
                    for (int E : mylist[D]) {
                        if (E==A) continue;
                        if (E==B) continue;
                        if (E==C) continue;
                        return true;
                    }
                }
            }
        }
        return false;
    }
    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int N, M, rfrom, rto;
        N = in.nextInt();
        M = in.nextInt();
        mylist = new ArrayList[N];
        for (int i = 0; i < N; i++) mylist[i] = new ArrayList<Integer>();
        
        while (M-- != 0) {
            rfrom = in.nextInt();
            rto = in.nextInt();
            mylist[rfrom].add(rto);
            mylist[rto].add(rfrom);
        }
        in.close();

        for (int i = 0; i < N; ++i){
            if (fivebridges(i)) {
                System.out.println(1);
                return;
            }
        }
        System.out.println(0);
    }
}