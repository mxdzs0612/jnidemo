// g++ src/JNIDemo.cpp -I $JAVA_HOME/include -I $JAVA_HOME/include/darwin -fPIC -shared -o libdemo.so
#include "JNIDemo.h"
#include <iostream>
#include <cstring>

using namespace std;

JNIEXPORT void JNICALL Java_JNIDemo_sayHello
  (JNIEnv *env, jobject obj, jstring str) {
    const char *text = env->GetStringUTFChars(str, 0);
    cout << "Hello from C++: " << text << endl;
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
  (JNIEnv *env, jobject obj, jint id, jstring name, jint sid, jstring sname) {
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

    env->SetIntField(newUserData, idField, id);
    env->SetObjectField(newUserData, nameField, name);
    env->SetIntField(newSchoolData, schoolIdField, sid);
    env->SetObjectField(newSchoolData, schoolNameField, sname);
    env->SetObjectField(newUserData, schoolField, newSchoolData);

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