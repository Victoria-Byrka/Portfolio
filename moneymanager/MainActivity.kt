// Victoria Byrka
package com.example.moneymanager

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.fragment.app.FragmentTransaction
import com.example.moneymanager.fragments.AddSomething
import com.example.moneymanager.fragments.Alarms
import com.example.moneymanager.fragments.AllMoney
import com.example.moneymanager.fragments.Home
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val homeFrag = Home()
        val allMoneyFrag = AllMoney()
        val alarmsFrag = Alarms()
        val addFrag = AddSomething()

        // allow navigation between fragments with the bottom navigation bar
        bottomNavigation.setOnNavigationItemSelectedListener {
            when(it.itemId){
                R.id.page_home ->{
                    supportFragmentManager.beginTransaction()
                        .replace(R.id.fragment, homeFrag)
                        .setTransition(FragmentTransaction.TRANSIT_FRAGMENT_OPEN)
                        .commit()
                }
                R.id.page_money ->{
                    supportFragmentManager.beginTransaction()
                        .replace(R.id.fragment, allMoneyFrag)
                        .setTransition(FragmentTransaction.TRANSIT_FRAGMENT_OPEN)
                        .commit()
                }
                R.id.page_alarms ->{
                    supportFragmentManager.beginTransaction()
                        .replace(R.id.fragment, alarmsFrag)
                        .setTransition(FragmentTransaction.TRANSIT_FRAGMENT_OPEN)
                        .commit()
                }
                R.id.page_add ->{
                    supportFragmentManager.beginTransaction()
                        .replace(R.id.fragment, addFrag)
                        .setTransition(FragmentTransaction.TRANSIT_FRAGMENT_OPEN)
                        .commit()
                }
            }
            true
        }
    }
}
