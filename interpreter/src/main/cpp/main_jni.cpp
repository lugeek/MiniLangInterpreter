#include <jni.h>
#include <string>
#include "InputProgram.h"
#include <android/log.h>

#include "lexer/lexer.h"
#include "parser/parser.h"
#include "visitor/xml_visitor.h"
#include "visitor/semantic_analysis.h"
#include "visitor/interpreter.h"
#include "table/table.h"

extern "C" JNIEXPORT void JNICALL
Java_com_lugeek_minilanginterpreter_Interpreter_initCInterpreter(
        JNIEnv *env, jobject instance) {
    auto* inputProgram = new InputProgram();
    InputProgram::setInputProgram(env, instance, inputProgram);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_lugeek_minilanginterpreter_Interpreter_inputLine(
        JNIEnv *env, jobject instance, jstring line) {
    InputProgram *inputProgram = InputProgram::getInputProgram(env, instance);
    inputProgram->input_line = InputProgram::jstring2string(env, line);

    std::string emptyCstring = std::string("");
    jstring emptyJstring = env->NewStringUTF(emptyCstring.c_str());

    // Quit
    if(inputProgram->input_line == "#quit"){
        inputProgram->program = "";
        inputProgram->expr = false;
        return emptyJstring;
    }
    // Clear Screen
    else if(inputProgram->input_line == "#clear"){
        return emptyJstring;
    }

    // Parse as program
    else {

        // Add line to program
        inputProgram->program += inputProgram->input_line + "\n";
        __android_log_print(ANDROID_LOG_INFO, "ljm", "%s", inputProgram->program.c_str());

        // Count number of open scopes
        unsigned int open_scopes = 0;
        open_scopes += std::count(inputProgram->program.begin(), inputProgram->program.end(), '{');
        open_scopes -= std::count(inputProgram->program.begin(), inputProgram->program.end(), '}');

        if (open_scopes) {
            return emptyJstring;
        }
    }

    try {

        // Tokenise and initialise parser
        lexer::Lexer lexer(inputProgram->program);
        parser::Parser parser(&lexer);
        parser::ASTProgramNode *prog;

        // Try to parse as program
        try {
            prog = parser.parse_program();
        }

            // Catch by trying to parse as expression
        catch(const std::exception &e) {

            try {
                // If expression ends with ';', get rid of it
                if (inputProgram->program.back() == ';')
                    inputProgram->program.pop_back();

                // Parse again, create program node manually
                lexer::Lexer expr_lexer(inputProgram->program);
                parser = parser::Parser(&expr_lexer, 0);  // do not consume first token
                prog = new parser::ASTProgramNode(
                        std::vector<parser::ASTNode *>({parser.parse_expression()}));

                inputProgram->expr = true;
            } catch(const std::exception &expr_e) {

                // Throw original error
                throw std::runtime_error(e.what());
            }
        }

        // Generate XML
        visitor::XMLVisitor xml_generator;
        xml_generator.visit(prog);


        // Try to analyse in a temporary copy of the global scope (just in case
        // the program is invalid)
        visitor::SemanticScope temp = inputProgram->semantic_global_scope_jni;
        visitor::SemanticAnalyser temp_semantic_analyser(&temp);
        temp_semantic_analyser.visit(prog);

        // If this succeeds, perform semantic analysis modifying global scope
        visitor::SemanticAnalyser semantic_analyser(&(inputProgram->semantic_global_scope_jni));
        semantic_analyser.visit(prog);

        // Interpreter
        visitor::Interpreter interpreter(&(inputProgram->interpreter_global_scope_jni));
        interpreter.visit(prog);

        __android_log_print(ANDROID_LOG_INFO, "ljm", inputProgram->expr ? "expr true" : "expr false");
        jstring result = emptyJstring;
        if(inputProgram->expr){
            auto current = interpreter.current_expr();
            switch(current.first){
                case parser::INT:
//                    std::cout << current.second.i;
//                    break;
                    __android_log_print(ANDROID_LOG_INFO, "ljm", "int");
                    result = env->NewStringUTF(std::to_string(current.second.i).c_str());
                    break;
                case parser::REAL:
//                    std::cout << current.second.r;
//                    break;
                    __android_log_print(ANDROID_LOG_INFO, "ljm", "real");
                    result = env->NewStringUTF(std::to_string(current.second.r).c_str());
                    break;
                case parser::BOOL:
//                    std::cout << ((current.second.b) ? "true" : "false");
//                    break;
                    __android_log_print(ANDROID_LOG_INFO, "ljm", "bool");
                    result = env->NewStringUTF(std::string((current.second.b) ? "true" : "false").c_str());
                    break;
                case parser::STRING:
//                    std::cout << current.second.s;
//                    break;
                    __android_log_print(ANDROID_LOG_INFO, "ljm", "string");
                    result = env->NewStringUTF(current.second.s.c_str());
                    break;
            }
        }
        inputProgram->program = "";
        inputProgram->expr = false;
        __android_log_print(ANDROID_LOG_INFO, "ljm", "return");
        return result;
    }

        // Catch exception and print error
    catch(const std::exception &e) {
//        std::cerr << e.what() << std::endl;
        return env->NewStringUTF(std::string(e.what()).c_str());
    }
    return env->NewStringUTF(std::string("error").c_str());
}

