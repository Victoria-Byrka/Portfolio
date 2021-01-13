package com.example.moneymanager.fragments

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView
import android.widget.Toast
import androidx.fragment.app.activityViewModels
import androidx.lifecycle.Observer
import androidx.navigation.fragment.findNavController
import androidx.recyclerview.widget.LinearLayoutManager
import com.example.moneymanager.R
import com.example.moneymanager.adapters.MoneyRecyclerAdapter
import com.example.moneymanager.datamodels.MoneyInfo
import com.example.moneymanager.viewmodels.MoneyViewModel
import kotlinx.android.synthetic.main.fragment_all_money.*
import kotlinx.android.synthetic.main.money_list_item.*

class AllMoney : Fragment() {

    private val moneyViewModel : MoneyViewModel by activityViewModels()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_all_money, container, false)
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        moneyList.layoutManager = LinearLayoutManager(activity)
        val adapter = MoneyRecyclerAdapter()
        moneyList.adapter = adapter

        moneyViewModel.moneyList.observe(viewLifecycleOwner, Observer { moneyList ->
            moneyList?.let { adapter.setMoney(it) }
        })


    }
}