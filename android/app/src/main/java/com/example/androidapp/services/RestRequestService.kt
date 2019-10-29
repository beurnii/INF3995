package com.example.androidapp.services

import android.content.Context
import com.android.volley.Request
import com.android.volley.Response
import com.android.volley.toolbox.StringRequest
import com.android.volley.toolbox.Volley
import com.example.androidapp.LoginRequest
import com.example.androidapp.LoginResponse
import kotlin.coroutines.resume
import kotlin.coroutines.suspendCoroutine
import kotlin.coroutines.resumeWithException

class RestRequestService(private val httpClient: HTTPRestClient, private val credentialsManager: CredentialsManager, private val context: Context) {
    private lateinit var serverUrl: String
    private val testToken = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJleHAiOjE1NzIzMjIxMzcsInBhc3N3b3JkIjoiMTIzNDUiLCJyb2xlIjoic3R1ZGVudCIsInVzZXJuYW1lIjoiYm91dGNob3UifQ.ld_skbUnXFUkC9aMHEpVq9PsYM3-d-y0YpBOAGz2efQ"

    init {
        credentialsManager.saveCredentials(context, testToken)
        initServerUrl("server")
    }

    fun initServerUrl(user: String) {
        val baseUrl = "https://us-central1-projet3-46f1b.cloudfunctions.net/getServerURL?user=$user"
        val request = StringRequest(
            Request.Method.GET, baseUrl, {
                serverUrl = "https://192.168.1.18:10000"
                httpClient.initHttps()
            }, {
                serverUrl = it.toString()
            })
        val requestQueue = Volley.newRequestQueue(context)
        requestQueue.add(request)
    }

    suspend fun getPingAsync(): String {
        return getAsync("ping")
    }

    suspend fun postLoginAsync(request: LoginRequest): LoginResponse {
        return postAsync("usager/login", request, LoginResponse::class.java)
    }

    suspend fun postLogoutAsync(): String {
        return postAsync("usager/logout", "", String::class.java)
    }

    private suspend fun getAsync(url: String): String {
        return suspendCoroutine { continuation ->
            val request = StringRequest("$serverUrl/$url",
                { response ->
                    continuation.resume(response)
                },
                {
                    continuation.resumeWithException(it)
                })
            httpClient.addToRequestQueue(request)
        }
    }

    private suspend fun <T> getAsync(url: String, classOfT: Class<T>): T {
        return baseRequestAsync(Request.Method.GET, url, "", classOfT)
    }

    private suspend fun <T> postAsync(url: String, data: Any, classOfT: Class<T>): T {
        return baseRequestAsync(Request.Method.POST, url, data, classOfT)
    }

    private suspend fun <T> baseRequestAsync(method: Int, url: String, data: Any, classOfT: Class<T>): T {
        return suspendCoroutine { continuation ->
            val request = GsonRequest(context, credentialsManager, method, "$serverUrl/$url", data, classOfT,
                mutableMapOf(
                    CredentialsManager.HTTP_HEADER_AUTHORIZATION to credentialsManager.getAuthToken(context)
                ),
                Response.Listener { response ->
                    continuation.resume(response)
                },
                Response.ErrorListener { continuation.resumeWithException(it) }
            )
            httpClient.addToRequestQueue(request)
        }
    }
}
