package com.example.androidapp.ui

import android.content.Intent
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import com.crashlytics.android.Crashlytics
import com.example.androidapp.R
import io.fabric.sdk.android.Fabric
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.Job
import kotlin.coroutines.CoroutineContext

class MainActivity : AppCompatActivity(), CoroutineScope {
    private lateinit var job: Job

    override val coroutineContext: CoroutineContext
        get() = job + Dispatchers.Main

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        Fabric.with(this, Crashlytics())
        job = Job()
        setContentView(R.layout.activity_main)

        findViewById<Button>(R.id.connection_btn).setOnClickListener { submitLogin() }
        findViewById<TextView>(R.id.register_btn).setOnClickListener { submitRegister() }
    }

    private fun submitLogin() {
        val username = findViewById<EditText>(R.id.username_val).text.toString()
        val password = findViewById<EditText>(R.id.password_val).text.toString()
        // TODO: Actually call the database
        if (username != "" && password == "1234") {
            val user = "$username;rooose;1234;$username@email.com;10" // information passed to the next activity
            val intent = Intent(this@MainActivity, SidePanelActivity::class.java).apply {
                putExtra("user", user)
            }
            startActivity(intent)
        }
    }

    private fun submitRegister() {
        // TODO : Decide how we want people to register. Do they send a request? Does the PC admin adds them?
        // val intent = Intent(this@MainActivity, RegisterActivity::class.java).apply { }
        // startActivity(intent)
    }
}
