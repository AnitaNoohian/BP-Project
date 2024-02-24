import java.util.Scanner;
public class test {


    public long factorial(int n) {
        if(n==1){
            return 1;
        }
        else{
            return n * factorial(n-1);
        }
    }

    public long fibonacci(int n) {
        if(n==1){
            return 1;
        }
        else if(n==2){
            return 1;
        }
        else{
            return fibonacci(n-1)+fibonacci(n-2);
        }
    }
    public static void main(String[] args) {
        int n;
        test obj = new test();
        Scanner in = new Scanner(System.in);
        n = in.nextInt();
        System.out.println(obj.factorial(n));
        n = in.nextInt();
        System.out.println(obj.fibonacci(n));

    }
}
