/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class JNIDemo */

#ifndef _Included_JNIDemo
#define _Included_JNIDemo
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     JNIDemo
 * Method:    sayHello
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_JNIDemo_sayHello
  (JNIEnv *, jobject, jstring);

/*
 * Class:     JNIDemo
 * Method:    sayHi
 * Signature: (CI)V
 */
JNIEXPORT void JNICALL Java_JNIDemo_sayHi
  (JNIEnv *, jobject, jchar, jint);

/*
 * Class:     JNIDemo
 * Method:    sayNo
 * Signature: (Z)Z
 */
JNIEXPORT jboolean JNICALL Java_JNIDemo_sayNo
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     JNIDemo
 * Method:    concat
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_JNIDemo_concat__Ljava_lang_String_2Ljava_lang_String_2
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     JNIDemo
 * Method:    concat
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_JNIDemo_concat__Ljava_lang_String_2
  (JNIEnv *, jobject, jstring);

/*
 * Class:     JNIDemo
 * Method:    createUser
 * Signature: (ILjava/lang/String;)LUser;
 */
JNIEXPORT jobject JNICALL Java_JNIDemo_createUser
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     JNIDemo
 * Method:    getUser
 * Signature: (LUser;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_JNIDemo_getUser
  (JNIEnv *, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif