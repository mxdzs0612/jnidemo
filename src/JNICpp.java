// jar cvfm cpp.jar src/MANIFEST.MF -C out/production/jnidemo/ JNICpp.class
// java -jar cpp.jar

public class JNICpp {
    public static void main(String[] args) {
        JNICpp cpp = new JNICpp();
        // test add
        System.out.printf("1 + 2 = %d\n", cpp.add(1, 2));

        // test toUpperCase
        String greeting = "hello, world!";
        System.out.printf("Upper case of \"%s\" is \"%s\"\n",
                greeting, cpp.toUpperCase(greeting));
    }

    public int add(int num1, int num2) {
        return num1 + num2;
    }

    public String toUpperCase(String str) {
        return str.toUpperCase();
    }
}
