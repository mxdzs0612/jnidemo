// 1、编写Java代码，准备清单文件
// 2、打包：jar cvfm cpp.jar src/MANIFEST.MF -C out/production/jnidemo/ JNICpp.class
// 3、编写C++代码，在C++中手动构建并销毁虚拟机，在中间增添要实现的内容，根据官方文档查找API实现所需的Java方法
// 4、编译：g++ -g src/main.cpp -I $JAVA_HOME/include -I $JAVA_HOME/include/darwin -ljvm -L $JAVA_HOME/lib/server/ -o jnicpp
// 5、运行测试：./jnicpp
#include <iostream>
#include <unordered_map>

#include "main.h"
#include "jni.h"

using namespace std;

int main(int argc, char* argv[])
{
    JNIEnv* env;
    JavaVM* jvm;

    env = create_vm(&jvm);
    jclass java_class = env->FindClass("JNICpp");

    if (java_class != 0) {
        // 重要：实例化
        // AllocObject仅仅构建一个新的类对象（仅仅为类对象分配内存空间而已），不初始成员变量，也不调用构造方法
        // NewObject需要指明调用的构造方法，构建一个新的类对象，并初始化成员变量，调用指定的构造方法
        jobject jobj = env->AllocObject(java_class);

        cout << "<<<<< From Java Main >>>>>" << endl;
        jmethodID methodId_main = env->GetStaticMethodID(java_class, "main", "([Ljava/lang/String;)V");
        env->CallStaticVoidMethod(java_class, methodId_main, "");

        cout << "<<<<< Use Java Add >>>>>" << endl;
        jmethodID methodId_add = env->GetMethodID(java_class, "add", "(II)I");
        if (methodId_add != 0) {
            int i = 2;
            auto iresult = env->CallIntMethod(jobj, methodId_add, i, i);
            cout << "Add result is " << iresult << endl;
        }
        print_exception(env);

        cout << "<<<<< Use Java toUpper >>>>>" << endl;
        jmethodID methodId_toUpper = env->GetMethodID(java_class, "toUpperCase", "(Ljava/lang/String;)Ljava/lang/String;");
        if (methodId_toUpper != 0) {
            const char* abc = "abc";
            jstring sresult = (jstring) env->CallObjectMethod(jobj, methodId_toUpper, env->NewStringUTF(abc));
            const char* newStr = env->GetStringUTFChars(sresult, 0);
            cout << "The upper case is: " << newStr << endl;
        }
        print_exception(env);

        cout << "<<<<< Use Java getMap >>>>>" << endl;
        jmethodID methodId_getMap = env->GetMethodID(java_class, "getMap", "()Ljava/util/HashMap;");
        if (methodId_getMap != 0) {
            std::unordered_map<int, std::string> um;
            auto m = env->CallObjectMethod(jobj, methodId_getMap);
            // 获取HashMap类和entrySet方法的ID
            jclass mapClass = env->GetObjectClass(m);
            jmethodID entrySetMethod = env->GetMethodID(mapClass, "entrySet", "()Ljava/util/Set;");
            jobject entrySetObj = env->CallObjectMethod(m, entrySetMethod);
            // 获取Set类和iterator方法的ID
            jclass setClass = env->GetObjectClass(entrySetObj);
            jmethodID iteratorMethod = env->GetMethodID(setClass, "iterator", "()Ljava/util/Iterator;");
            // 获取Iterator类和hasNext、next方法的ID
            jobject iteratorObj = env->CallObjectMethod(entrySetObj, iteratorMethod);
            jclass mapEntryClass = env->FindClass("java/util/Map$Entry");
            jclass integerClass = env->FindClass("java/lang/Integer");
            // 获取Map.Entry类和getKey、getValue方法的ID
            jmethodID getKeyMethod = env->GetMethodID(mapEntryClass, "getKey", "()Ljava/lang/Object;");
            jmethodID getValueMethod = env->GetMethodID(mapEntryClass, "getValue", "()Ljava/lang/Object;");

            jmethodID intValueMethod = env->GetMethodID(integerClass, "intValue", "()I");
            // 遍历HashMap，将键和值存储到unordered_map中
            while (env->CallBooleanMethod(iteratorObj, env->GetMethodID(env->GetObjectClass(iteratorObj), "hasNext", "()Z"))) {
                jobject entryObj = env->CallObjectMethod(iteratorObj, env->GetMethodID(env->GetObjectClass(iteratorObj), "next", "()Ljava/lang/Object;"));
                auto integerObj = env->CallObjectMethod(entryObj, getKeyMethod);
                jint keyObj = env->CallIntMethod(integerObj, intValueMethod);
                jstring valueObj = (jstring)env->CallObjectMethod(entryObj, getValueMethod);
                int k = (int) keyObj;
                std::string v = jstringToString(env, valueObj);
                um[k] = v;
            }
            for (const auto& pair : um) {
                std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
            }
        }
    }
    jvm->DestroyJavaVM();
    return 0;
}

JNIEnv* create_vm(JavaVM ** jvm)
{
    JNIEnv *env;
    JavaVMInitArgs vm_args;
    vm_args.version = JNI_VERSION_10;
    // JVM参数，如有更多需增大数组容量
    JavaVMOption* options = new JavaVMOption[1];
    options[0].optionString = (char *) "-Djava.class.path=cpp.jar";
    vm_args.nOptions = 1;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = 0;

    int ret = JNI_CreateJavaVM(jvm, (void**) &env, &vm_args);
    if (ret < 0) cout << "<<<<< Unable to Launch JVM >>>>>" << endl;
    return env;
}

void print_exception(JNIEnv* env) {
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
}

std::string jstringToString(JNIEnv* env, jstring jstr) {
    const char* cstr = env->GetStringUTFChars(jstr, nullptr);
    std::string str(cstr);
    env->ReleaseStringUTFChars(jstr, cstr);
    return str;
}