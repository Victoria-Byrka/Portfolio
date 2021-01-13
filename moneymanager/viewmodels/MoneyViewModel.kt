package com.example.moneymanager.viewmodels

import android.app.Application
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import com.example.moneymanager.datamodels.MoneyInfo
import com.example.moneymanager.datasources.MoneyDataSource

class MoneyViewModel(application: Application) : AndroidViewModel(application) {
    val moneyList : MutableLiveData<List<MoneyInfo>> = MutableLiveData()

    init {
        loadMoney()
    }

    private fun loadMoney() {
        moneyList.value = MoneyDataSource.money
    }

    fun addMoney(money : MoneyInfo) {
        MoneyDataSource.money.add(money)
        moneyList.value = MoneyDataSource.money
    }

}