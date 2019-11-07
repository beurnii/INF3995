package com.example.androidapp

import com.example.androidapp.fragments.searchCourse.course.CourseItem
import com.google.gson.annotations.SerializedName

data class LoginRequest(
    @SerializedName("usager") val username: String,
    @SerializedName("mot_de_passe") val password: String
)

data class LoginResponse(
    @SerializedName("edition") val edition: Boolean
)

data class PasswordRequest(
    @SerializedName("ancien") val oldPassword: String,
    @SerializedName("nouveau") val newPassword: String
)

data class TransactionRequest(
    @SerializedName("sigle") val classCode: String,
    @SerializedName("nom") val className: String,
    @SerializedName("trimestre") val trimester: Number,
    @SerializedName("resultats") val results: List<StudentItem>,
    @SerializedName("pdf") val pdf: String
)

data class StudentItem(
    @SerializedName("nom") val lastName: String,
    @SerializedName("prenom")val firstName: String,
    @SerializedName("matricule") val code: String,
    @SerializedName("note") val grade: String
)

data class ListStudent(
    @SerializedName("listeEtudiant") val listeEtudiant: List<StudentItem>
)

data class ListClass(
    @SerializedName("listeClasses") val listeClasses: List<CourseItem>
)
