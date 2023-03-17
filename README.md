## Java调用C++ ##
1. 编辑Java文件JNIDemo、User
2. 生成头文件 javac -h -jni -classpath out/production/jnidemo -d src JNIDemo  
   JDK11+: javac -encoding utf8 -h src src/JNIDemo.java src/User.java
3. 编写C++文件，编译生成动态链接库 g++ src/JNIDemo.cpp -I $JAVA_HOME/include -I $JAVA_HOME/include/darwin -fPIC -shared -o libdemo.so
4. 补充Java代码，调用所需的类，运行

## C++调用Java ##
1. 编写Java代码JNICpp，准备清单文件
2. 打包：jar cvfm cpp.jar src/MANIFEST.MF -C out/production/jnidemo/ JNICpp.class
3. 编写C++代码，在C++中手动构建并销毁虚拟机，在中间增添要实现的内容，根据官方文档查找API实现所需的Java方法
4. 编译：g++ -g src/main.cpp -I $JAVA_HOME/include -I $JAVA_HOME/include/darwin -ljvm -L $JAVA_HOME/lib/server/ -o jnicpp
5. 运行测试：./jnicpp

也可使用CMake：
1. mkdir build && cd build
2. cmake ..
3. cmake --build .
4. ./JniDemoCpp