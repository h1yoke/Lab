
import java.util.Scanner;
import java.math.BigInteger;

public class TaskH {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        BigInteger
            w = BigInteger.valueOf(sc.nextInt()),
            h = BigInteger.valueOf(sc.nextInt()),
            n = BigInteger.valueOf(sc.nextInt());

        System.out.println(binSearch(w, h, n));
    }

    static BigInteger binSearch(BigInteger w, BigInteger h, BigInteger n) {
        BigInteger
            l = new BigInteger("0"),
            r = new BigInteger("1000000000000000000"); // 1e18

        for (int i = 0; i < 1e6; i++) {
            BigInteger m = l.add(r).divide(BigInteger.valueOf(2));

            // (m / w) * (m / h)
            int res = m.divide(w).multiply(m.divide(h)).compareTo(n);
            if (res < 0) {
                l = m;
            } else {
                r = m;
            }
        }
        return r;
    }
}