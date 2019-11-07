package com.example.androidapp.fragments.searchStudent.student

import java.util.ArrayList
import java.util.HashMap
import com.example.androidapp.StudentItem

/**
 * Helper class for providing sample content for user interfaces created by
 * Android template wizards.
 *
 */
object StudentContent {

    /**
     * An array of student items.
     */
    val items: MutableList<StudentItem> = ArrayList()

    /**
     * A map of student items, by ID.
     */
    private val item_map: MutableMap<String, StudentItem> = HashMap()

    private const val COUNT = 25
    private const val BASE_STUDENT_CODE = 1800000

    init {
        // Add some sample items.
        // TODO: Fill with information from database

    }

     fun addItem(item: StudentItem) {
        items.add(item)
        item_map[item.code] = item
    }

    fun clearList() {
        items.clear()
    }
}
