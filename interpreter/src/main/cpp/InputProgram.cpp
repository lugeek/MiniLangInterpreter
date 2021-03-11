#include "InputProgram.h"

InputProgram::InputProgram() = default;

void InputProgram::setInputProgram(JNIEnv *env, jobject instance, InputProgram *inputProgram) {
    jclass clazz = env->GetObjectClass(instance);
    jfieldID fid = env->GetFieldID(clazz, "cObjPoint", "J");
    env->SetLongField(instance, fid, (jlong)inputProgram);
}

InputProgram *InputProgram::getInputProgram(JNIEnv *env, jobject instance) {
    jclass clazz = env->GetObjectClass(instance);
    jfieldID fid = env->GetFieldID(clazz, "cObjPoint", "J");
    jlong p = env->GetLongField(instance, fid);
    return (InputProgram*)p;
}

std::string InputProgram::jstring2string(JNIEnv *env, jstring jStr) {
    if (!jStr)
        return "";

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char *)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}
