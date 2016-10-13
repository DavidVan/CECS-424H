import java.util.Arrays;

/**
 * Created by David on 10/13/2016.
 */
public class WrongSwap {

    public static void main(String[] args) {
        int[] arr = new int[] {1, 2, 3, 4, 5};
        wrongSwap(arr[0], arr[4]);
        System.out.println(Arrays.toString(arr));
        rightSwap(arr, 0, 4);
        System.out.println(Arrays.toString(arr));
    }

    public static void wrongSwap(int a, int b) {
        int temp = a;
        a = b;
        b = temp;
    }

    public static void rightSwap(int[] arr, int a, int b) {
        int temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }

}
