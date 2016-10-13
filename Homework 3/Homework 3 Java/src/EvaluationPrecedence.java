/**
 * Created by David on 10/13/2016.
 */
public class EvaluationPrecedence {

    public static void main(String[] args) {
        int x = 3;
        A(B(), C(2 + x)); // First Example
        A(C(2 + x), B()); // Second Example
    }

    public static void A(int b, int c) {
        System.out.println("This is A!");
        System.out.println("b = " + b);
        System.out.println("c = " + c);
    }

    public static int B() {
        System.out.println("This is B!");
        return 2;
    }

    public static int C(int x) {
        System.out.println("This is C!");
        return 2 + x;
    }

}
