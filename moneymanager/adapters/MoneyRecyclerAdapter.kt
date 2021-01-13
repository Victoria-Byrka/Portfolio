package com.example.moneymanager.adapters

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.example.moneymanager.R
import com.example.moneymanager.datamodels.MoneyInfo

class MoneyRecyclerAdapter() : RecyclerView.Adapter<MoneyRecyclerAdapter.ViewHolder>() {

    private var moneys = emptyList<MoneyInfo>()

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val layoutInflater = LayoutInflater.from(parent.context)
        val itemView = layoutInflater.inflate(R.layout.money_list_item, parent, false)
        return ViewHolder(itemView)
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val money = moneys[position]
        holder.moneyTitle?.text = money.title
        holder.moneyBody?.text = money.body
        holder.moneyType?.text = money.type
        holder.moneyDate?.text = money.date
        holder.moneyPosition = position
    }

    override fun getItemCount(): Int {
        return moneys.size
    }

    inner class ViewHolder(itemView: View?) : RecyclerView.ViewHolder(itemView!!) {
        val moneyTitle = itemView?.findViewById<TextView>(R.id.moneyDescTextView)
        val moneyBody = itemView?.findViewById<TextView>(R.id.moneyAmountTextView)
        val moneyType = itemView?.findViewById<TextView>(R.id.moneyTypeTextView)
        val moneyDate = itemView?.findViewById<TextView>(R.id.moneyDateTextView)
        var moneyPosition = 0
    }

    fun setMoney(moneys : List<MoneyInfo>) {
        this.moneys = moneys
        notifyDataSetChanged()
    }

}