/*
 Copyright 2019 mirza baig

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
        limitations under the License.
*/



#include <jni.h>
#include <stdio.h>
#include <pthread.h>

static JavaVM* jvm = 0;
static jobject activity = 0;

void* myThreadFun(void*);

struct MyStructure{
    int k=0;
    int h=0;
    struct InsideMyStructure{
        int insidek=0;
    }insideMyStructure;
}myStructure;


extern "C" JNIEXPORT jobject
JNICALL
Java_com_seahawk_hello_1cmake_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject mainActivity /* this */) {

//conditional compilation for predefined macros
#if defined(__arm__)
#if defined(__ARM_ARCH_7A__)
#if defined(__ARM_NEON__)
#if defined(__ARM_PCS_VFP)
#define ABI "armeabi-v7a/NEON (hard-float)"
#else
#define ABI "armeabi-v7a/NEON"
#endif
#else
#if defined(__ARM_PCS_VFP)
#define ABI "armeabi-v7a (hard-float)"
#else
#define ABI "armeabi-v7a"
#endif
#endif
#else
#define ABI "armeabi"
#endif
#elif defined(__i386__)
#define ABI "x86"
#elif defined(__x86_64__)
#define ABI "x86_64"
#elif defined(__mips64)  /* mips64el-* toolchain defines __mips__ too */
#define ABI "mips64"
#elif defined(__mips__)
#define ABI "mips"
#elif defined(__aarch64__)
#define ABI "arm64-v8a"
#else
#define ABI "unknown"
#endif


    //This is the wrapper class of MyStructure datastructure in c above is the declaration  which is in java
    jclass myjclass = (*env).FindClass("com/seahawk/hello_cmake/MyStructure");
    if(NULL == myjclass)return NULL;

    //methodID of constructor
    jmethodID myjclassmethodID = (*env).GetMethodID(myjclass,"<init>","(II)V");
    if(NULL == myjclassmethodID)return NULL;

    //argument of the constructor
    jvalue args[2];
    args[0].i=myStructure.k=40;
    args[1].i=myStructure.insideMyStructure.insidek=30;


    //object creation
    jobject myjobject = (*env).NewObjectA(myjclass,myjclassmethodID,args);
    if(NULL == myjobject)return NULL;

    //get the class from MainActivity
    jclass thisClass = (*env).GetObjectClass(mainActivity);
    if(NULL == thisClass)return NULL;

    //method id of callback
    jmethodID midCallBackStr = (*env).GetMethodID(thisClass,"callback","()V");
    if(NULL == midCallBackStr)return NULL;

     //calling callback
    (*env).CallVoidMethod(mainActivity,midCallBackStr);

    //getting the jvm and activity
    (*env).GetJavaVM(&jvm);
    activity = (*env).NewGlobalRef(mainActivity);


    //calling  worker thread
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, myThreadFun, NULL);
    pthread_join(thread_id, NULL);


    return myjobject;
}

//function which will run in separate worker thread
void* myThreadFun(void*)
{
    JNIEnv* env = NULL;
    (*jvm).AttachCurrentThread(&env, NULL);
    jclass clazz = (*env).GetObjectClass(activity);
    jmethodID  methodID = (*env).GetMethodID(clazz,"callbackFromWorkerThread","()V");
    (*env).CallVoidMethod(activity, methodID);
    (*jvm).DetachCurrentThread();
    return NULL;
}
