package com.lugeek.minilanginterpreter

class Interpreter {

    companion object {
        init {
            System.loadLibrary("minilang-interpreter")
        }
    }

    val cObjPoint: Long = 0 // 虚拟机是32位用int，真机是64位用long

    external fun initCInterpreter()
    external fun inputLine(line: String): String
}