package com.lugeek.minilanginterpreter.sample

import android.content.Context
import android.util.AttributeSet
import android.util.Log
import android.view.KeyEvent
import com.lugeek.minilanginterpreter.Interpreter

class EnterEditText @JvmOverloads constructor(
    context: Context, attrs: AttributeSet? = null, defStyleAttr: Int = android.R.attr.editTextStyle
) : androidx.appcompat.widget.AppCompatEditText(context, attrs, defStyleAttr) {

    val interpreter = Interpreter()
    var lineIndex = 0

    init {
        interpreter.initCInterpreter()
    }

    override fun onKeyUp(keyCode: Int, event: KeyEvent?): Boolean {
        if (keyCode == KeyEvent.KEYCODE_ENTER) {
            val lineArray : List<String>? = this.text?.split('\n')?.filter { it != "" }
            val line = lineArray?.elementAtOrNull(lineIndex)
            line?.let {
                val result = interpreter.inputLine(line)
                lineIndex++
                if (result.isNotEmpty()) {
                    this.append(">$result\n\n")
                    lineIndex++
                }
            }
        }
        return super.onKeyUp(keyCode, event)
    }
}