#include <jni.h>
#include <string>
#include <android/native_activity.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_piercelbrooks_sfml_app_MainActivity_getBaseNativeClass(JNIEnv* env, jobject) {
#ifdef SFML_JNI_CLASS
    return env->NewStringUTF(SFML_JNI_CLASS);
#else
    return NULL;
#endif
}

void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize) {

}
