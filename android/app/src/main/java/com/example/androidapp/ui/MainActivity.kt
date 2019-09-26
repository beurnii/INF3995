package com.example.androidapp.ui

import android.os.Bundle
import android.view.MenuItem
import android.widget.Button
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.ActionBar
import androidx.appcompat.app.AppCompatActivity
import androidx.appcompat.widget.Toolbar
import androidx.core.view.GravityCompat
import androidx.drawerlayout.widget.DrawerLayout
import com.crashlytics.android.Crashlytics
import io.fabric.sdk.android.Fabric
import com.example.androidapp.R
import com.google.android.material.navigation.NavigationView
import kotlinx.coroutines.*
import org.koin.android.ext.android.inject
import kotlin.coroutines.CoroutineContext

class MainActivity : AppCompatActivity(), MainContract.View, CoroutineScope {

    private val controller: MainContract.Controller by inject()
    private lateinit var drawerLayout: DrawerLayout
    private lateinit var toolbar: Toolbar
    private lateinit var navView: NavigationView
    private lateinit var textView: TextView
    private lateinit var job: Job

    override val coroutineContext: CoroutineContext
        get() = job + Dispatchers.Main

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        Fabric.with(this, Crashlytics())
        job = Job()

        setContentView(R.layout.activity_main)

        toolbar = findViewById(R.id.toolbar)
        drawerLayout = findViewById(R.id.drawerLayout)
        navView = findViewById(R.id.navView)
        textView = findViewById(R.id.lolVar)

        setSupportActionBar(toolbar)

        val actionbar: ActionBar? = supportActionBar
        actionbar?.apply {
            setDisplayHomeAsUpEnabled(true)
            setHomeAsUpIndicator(R.drawable.ic_menu)
        }

        navView.setNavigationItemSelectedListener { menuItem ->
            menuItem.isChecked = true
            drawerLayout.closeDrawers()

            when (menuItem.itemId) {
                R.id.actionHome -> {
                    Toast.makeText(this, "Home", Toast.LENGTH_LONG).show()
                }
                R.id.actionSettings -> {
                    Toast.makeText(this, "Settings", Toast.LENGTH_LONG).show()
                }
            }
            true
        }

        findViewById<TextView>(R.id.lolVar).text = "lol!"
        findViewById<Button>(R.id.refreshBtn).setOnClickListener { launch {
            try {
                textView.text = controller.onRefreshLolAsync()
            } catch (e: Exception) {
                textView.text = getString(R.string.errorMessageUnknown)
            }
        } }
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        return when (item.itemId) {
            android.R.id.home -> {
                drawerLayout.openDrawer(GravityCompat.START)
                true
            }
            else -> super.onOptionsItemSelected(item)
        }
    }
}