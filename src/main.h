#include "jni.h"

#ifndef SRC_MAIN_H
#define SRC_MAIN_H


class main {

};

JNIEnv* create_vm(JavaVM **);
void print_exception(JNIEnv*);
std::string jstringToString(JNIEnv* env, jstring jstr);

#endif //SRC_MAIN_H
