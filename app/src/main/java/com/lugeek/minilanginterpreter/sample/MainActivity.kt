package com.lugeek.minilanginterpreter.sample

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.text.Editable
import android.text.InputType
import android.text.TextWatcher
import android.util.Log
import android.view.KeyEvent
import android.view.View
import android.view.inputmethod.EditorInfo
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast
import com.lugeek.minilanginterpreter.Interpreter

class MainActivity : AppCompatActivity() {

    var editText:EditText? = null
    var idx = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val interpreter = Interpreter()
        interpreter.initCInterpreter()
        editText = findViewById<EditText>(R.id.edit_text)
//        editText?.setImeOptions(EditorInfo.IME_ACTION_DONE);
//        editText?.setRawInputType(InputType.TYPE_CLASS_TEXT);

//        editText?.addTextChangedListener(object : TextWatcher{
//            override fun beforeTextChanged(s: CharSequence?, start: Int, count: Int, after: Int) {
//            }
//
//            override fun onTextChanged(s: CharSequence?, start: Int, before: Int, count: Int) {
//            }
//
//            override fun afterTextChanged(s: Editable?) {
//                val text = s.toString()
//                val isEnter = text.last() == '\n'
//                if (isEnter) {
//                    val lines = text.split('\n').filter { it != "" }
//                    if (idx < lines.count()) {
//                        val line = lines[idx]
//                        idx++
//                        Log.i("ljm", "start inputLine")
//                        val result = interpreter.inputLine(line)
//                        if (result.isNotEmpty()) {
//                            editText?.append("\n"+result+"\n")
//                            idx = editText?.text?.split('\n')?.filter { it != "" }?.count() ?: 0
//                        }
//                    }
//                }
//            }
//        })
//        editText?.setOnKeyListener(View.OnKeyListener { v, keyCode, event ->
//            if (keyCode == KeyEvent.KEYCODE_ENTER && event.action == KeyEvent.ACTION_UP) {
//                Toast.makeText(this@MainActivity, "enter", Toast.LENGTH_LONG).show()
//                return@OnKeyListener true
//            }
//            false
//        })
//        editText?.setOnEditorActionListener(TextView.OnEditorActionListener { v, actionId, event ->
//            editText?.append("\n")
//            Toast.makeText(this@MainActivity, "enter", Toast.LENGTH_LONG).show()
//            true
//        })
    }
}