// g++ src/JNIDemo.cpp -I $JAVA_HOME/include -I $JAVA_HOME/include/darwin -fPIC -shared -o libdemo.so
#include "JNIDemo.h"
#include <iostream>
#include <cstring>
#include <unordered_map>

using namespace std;

JNIEXPORT void JNICALL Java_JNIDemo_sayHello
  (JNIEnv *env, jobject obj, jstring str) {
    const char *text = env->GetStringUTFChars(str, 0);
    cout << "Hello from C++: " << text << endl;
    env->ReleaseStringUTFChars(str, text);
}


JNIEXPORT void JNICALL Java_JNIDemo_sayHi
  (JNIEnv *env, jobject obj, jchar c, jint i) {
    cout << "Hi from C++: " << c << " " << char(c) << " " << i << endl;
}

JNIEXPORT jboolean JNICALL Java_JNIDemo_sayNo
  (JNIEnv *env, jobject obj, jboolean b) {
    return !b;
}

JNIEXPORT jstring JNICALL Java_JNIDemo_concat__Ljava_lang_String_2Ljava_lang_String_2
  (JNIEnv *env, jobject obj, jstring a, jstring b) {
    const char *as = env->GetStringUTFChars(a, 0);
    const char *bs = env->GetStringUTFChars(b, 0);
    char *concatenated = new char[strlen(as) + strlen(bs) + 1];
    strcpy(concatenated, as);
    strcat(concatenated, bs);
    jstring res = env->NewStringUTF(concatenated);
    return res;
}

JNIEXPORT jstring JNICALL Java_JNIDemo_concat__Ljava_lang_String_2
  (JNIEnv *env, jobject obj, jstring a) {
    const char *as = env->GetStringUTFChars(a, 0);
    char *concatenated = new char[strlen(as) + strlen("def") + 1];
    strcpy(concatenated, as);
    strcat(concatenated, "def");
    jstring res = env->NewStringUTF(concatenated);
    return res;
}

JNIEXPORT jobject JNICALL Java_JNIDemo_createUser
  (JNIEnv *env, jobject obj, jint id, jstring name, jint sid, jstring sname, jobject map) {
    // Create the object of the class UserData
    jclass userDataClass = env->FindClass("User");
    jobject newUserData = env->AllocObject(userDataClass);

    jclass userSchoolClass = env->FindClass("User$UserSchool");
    jobject newSchoolData = env->AllocObject(userSchoolClass);

    // Get the UserData fields to be set
    jfieldID idField = env->GetFieldID(userDataClass , "id", "I");
    jfieldID nameField = env->GetFieldID(userDataClass , "name", "Ljava/lang/String;");
    jfieldID schoolField = env->GetFieldID(userDataClass , "userSchool", "LUser$UserSchool;");
    jfieldID schoolIdField = env->GetFieldID(userSchoolClass , "sId", "I");
    jfieldID schoolNameField = env->GetFieldID(userSchoolClass , "sName", "Ljava/lang/String;");
    jfieldID scoreField = env->GetFieldID(userDataClass , "score", "Ljava/util/Map;");

    env->SetIntField(newUserData, idField, id);
    env->SetObjectField(newUserData, nameField, name);
    env->SetIntField(newSchoolData, schoolIdField, sid);
    env->SetObjectField(newSchoolData, schoolNameField, sname);
    env->SetObjectField(newUserData, schoolField, newSchoolData);
    env->SetObjectField(newUserData, scoreField, map);

    return newUserData;
}

JNIEXPORT jstring JNICALL Java_JNIDemo_getUser
  (JNIEnv *env, jobject obj, jobject user) {
    // Find the id of the Java method to be called
    jclass userDataClass = env->GetObjectClass(user);
    jmethodID methodId = env->GetMethodID(userDataClass, "getUserInfo", "()Ljava/lang/String;");

    jstring result = (jstring) env->CallObjectMethod(user, methodId);
    return result;
}

JNIEXPORT jobject JNICALL Java_JNIDemo_testMap
  (JNIEnv *env, jobject obj, jobjectArray args) {
    std::unordered_map<long, std::string> um;
    for (int i = 0; i < env->GetArrayLength(args) - 1; i += 2) {
      jlong jKey = (jlong) env->GetObjectArrayElement(args, i);
      jstring jValue = (jstring) env->GetObjectArrayElement(args, i + 1);
      const char *value = env->GetStringUTFChars(jValue, nullptr);
      um[jKey] = value;
      env->ReleaseStringUTFChars(jValue, value);
    }
    jclass hashMapClass = env->FindClass("java/util/HashMap");
    // jmethodID hashMapCtor = env->GetMethodID(hashMapClass, "<init>", "()V");
    // jobject hashMap = env->NewObject(hashMapClass, hashMapCtor);
    jobject hashMap = env->AllocObject(hashMapClass);
    jmethodID hashMapPut = env->GetMethodID(hashMapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
    for (auto& [key, value] : um) {
      // 也可用类似pair.first()的方法
      jlong jKey = (jlong) key;
      jstring jValue = env->NewStringUTF(value.c_str());
      env->CallObjectMethod(hashMap, hashMapPut, jKey, jValue);
      env->DeleteLocalRef(jValue);
    }
    return hashMap;
}

JNIEXPORT void JNICALL Java_JNIDemo_testStatic
  (JNIEnv *env, jclass cls, jobject javaList) {
  // 获取List对象的长度
  jclass listClass = env->GetObjectClass(javaList);
  jmethodID sizeMethod = env->GetMethodID(listClass, "size", "()I");
  jint size = env->CallIntMethod(javaList, sizeMethod);

  // 将List中的元素存储在jobject数组中
  jobjectArray javaArray = env->NewObjectArray(size, env->FindClass("java/lang/Object"), NULL);
  for (int i = 0; i < size; i++) {
      jmethodID getMethod = env->GetMethodID(listClass, "get", "(I)Ljava/lang/Object;");
      jobject item = env->CallObjectMethod(javaList, getMethod, i);
      env->SetObjectArrayElement(javaArray, i, item);
  }

  // 输出jobject数组中的元素
  for (int i = 0; i < size; i++) {
      jstring item = (jstring) env->GetObjectArrayElement(javaArray, i);
      const char* itemChars = env->GetStringUTFChars(item, NULL);
      cout << "List element: " << i << ":" << itemChars << endl;
      env->ReleaseStringUTFChars(item, itemChars);
  }
}