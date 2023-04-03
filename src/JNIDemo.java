// 1、编辑Java文件
// 2、生成头文件 JDK11+不需要写-jni: javac -encoding utf8 -h src -d out/production/jnidemo src/JNIDemo.java src/User.java
// 3、编写C++文件，编译生成动态链接库 g++ src/JNIDemo.cpp -I $JAVA_HOME/include -I $JAVA_HOME/include/darwin -fPIC -shared -o libdemo.so
// 4、补充Java代码，运行

import java.util.Map;

public class JNIDemo {
    static {
        try {
            String path = JNIDemo.class.getClassLoader().getResource("//").getPath();
            // For MAC: DYLD_LIBRARY_PATH
            System.load(path + "../../../libdemo.so");
            System.out.println("Load library success");
        } catch (UnsatisfiedLinkError e) {
            System.out.println("Cannot load library!\n" + e);
            String libraryDirs = System.getProperty("java.library.path");
            System.out.println(libraryDirs);
        }
    }

    public native void sayHello(String name);
    public native void sayHi(char c, int i);

    public native boolean sayNo(boolean b);

    public native String concat(String a, String b);

    public native String concat(String a);

    public native User createUser(int id, String name, int sid, String sname);

    public native String getUser(User user);

    public native Map<Long, String> testMap(Object... objects);

    public static void main(String[] args) {
        JNIDemo demo = new JNIDemo();
        demo.sayHello("my");
        demo.sayHi('a', 2);
        System.out.println(demo.sayNo(true));
        System.out.println(demo.concat("abc", "def"));
        System.out.println(demo.concat("abc"));
        User john = demo.createUser(1, "John", 0, "HUST");
        System.out.println(demo.getUser(john));
        System.out.println(demo.testMap(1, "a", 2, "b", "9333333333333333333333339", "pscrpscrpscr"));
    }
}