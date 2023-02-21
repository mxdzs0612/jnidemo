public class Main {
    public static void main(String[] args) {
        System.out.println("Hello world!");
        String libraryDirs = System.getProperty("java.library.path");
        // /Users/jmy/Library/Java/Extensions:/Library/Java/Extensions:/Network/Library/Java/Extensions:/System/Library/Java/Extensions:/usr/lib/java:.
        System.out.println(libraryDirs);
    }
}