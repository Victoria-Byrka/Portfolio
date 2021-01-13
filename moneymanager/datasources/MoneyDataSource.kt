package com.example.moneymanager.datasources

import com.example.moneymanager.datamodels.MoneyInfo

object MoneyDataSource {
    val money = ArrayList<MoneyInfo>();

    init {
        initializeMoney();
    }

    // pre-set values. can be removed
    private fun initializeMoney() {
        var moneyIn = MoneyInfo("Wifi", "$50", "Expense", "12/1/2020")
        money.add(moneyIn)
        moneyIn = MoneyInfo("Phone", "$100", "Expense", "11/30/2020")
        money.add(moneyIn)
        moneyIn = MoneyInfo("Work", "$2000", "Income", "12/3/2020")
        money.add(moneyIn)
    }
}