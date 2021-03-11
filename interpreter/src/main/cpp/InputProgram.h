//
// Created by lugeek on 2021/3/10.
//

#ifndef MINILANGINTERPRETER_INPUTPROGRAM_H
#define MINILANGINTERPRETER_INPUTPROGRAM_H

#include <string>
#include <jni.h>

#include "visitor/semantic_analysis.h"
#include "visitor/interpreter.h"

class InputProgram {
public:
    InputProgram();
    std::string input_line;
    std::string program;
    bool expr = false;
    visitor::SemanticScope semantic_global_scope_jni;
    visitor::InterpreterScope interpreter_global_scope_jni;
    static void setInputProgram(JNIEnv *env, jobject instance, InputProgram *inputProgram);// 将InputProgram的C++对象指针传递给Java对象
    static InputProgram* getInputProgram(JNIEnv *env, jobject instance);// 从Java对象获取InputProgram的C++对象
    static std::string jstring2string(JNIEnv *env, jstring jStr);
};

#endif //MINILANGINTERPRETER_INPUTPROGRAM_H
