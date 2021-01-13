package com.example.moneymanager.fragments

import android.os.Build
import android.os.Bundle
import android.text.Layout
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.*
import androidx.annotation.RequiresApi
import androidx.constraintlayout.widget.ConstraintSet
import androidx.fragment.app.activityViewModels
import androidx.fragment.app.viewModels
import androidx.lifecycle.LifecycleOwner
import androidx.lifecycle.MutableLiveData
import com.example.moneymanager.R
import com.example.moneymanager.datamodels.MoneyInfo
import com.example.moneymanager.datasources.MoneyDataSource.money
import com.example.moneymanager.viewmodels.MoneyViewModel
import kotlinx.android.synthetic.main.fragment_add_something.*
import kotlinx.android.synthetic.main.fragment_home.*
import java.util.Observer

class Home : Fragment() {

    private val moneyViewModel : MoneyViewModel by activityViewModels()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_home, container, false)
    }

    @RequiresApi(Build.VERSION_CODES.N)
    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        // find add button and done button
        val addBudgetBtn = view.findViewById(R.id.addBudget) as Button
        val doneBtn = view.findViewById(R.id.doneEditButton) as Button

        // find display texts
        val spentPercentText = view.findViewById(R.id.progressTextView) as TextView
        val maxBudgetDisplayText = view.findViewById(R.id.maxBudget) as TextView
        val textHint = view.findViewById(R.id.textHint) as TextView
        val spentHint = view.findViewById(R.id.spentHint) as TextView

        // find edit text
        val monthlyBudgetEditText = view.findViewById(R.id.maxBudgetInputField) as EditText
        val budgetSpent = view.findViewById(R.id.monthlySpent) as EditText

        // find progress bar
        val progressBar = view.findViewById(R.id.progressBar) as ProgressBar

        // hide edit fields until needed
        monthlyBudgetEditText.visibility = View.INVISIBLE
        budgetSpent.visibility = View.INVISIBLE
        doneBtn.visibility = View.INVISIBLE
        textHint.visibility = View.INVISIBLE
        spentHint.visibility = View.INVISIBLE

        // add/edit button clicked
        addBudgetBtn.setOnClickListener {
            // tell user they are in edit mode
            Toast.makeText(activity, "Editing Monthly Budget", Toast.LENGTH_SHORT).show()
            // show all edit options
            monthlyBudgetEditText.visibility = View.VISIBLE
            budgetSpent.visibility = View.VISIBLE
            doneBtn.visibility = View.VISIBLE
            textHint.visibility = View.VISIBLE
            spentHint.visibility = View.VISIBLE

            // hide add/edit button and progress bar fields
            addBudgetBtn.visibility = View.INVISIBLE
            progressBar.visibility = View.INVISIBLE

        }
        // done button clicked
        doneEditButton.setOnClickListener {
            // hide edit fields until needed again
            monthlyBudgetEditText.visibility = View.INVISIBLE
            budgetSpent.visibility = View.INVISIBLE
            doneBtn.visibility = View.INVISIBLE
            textHint.visibility = View.INVISIBLE
            spentHint.visibility = View.INVISIBLE

            // find user budget entered
            val userBudget = monthlyBudgetEditText.text.toString().toInt()
            // display user budget and set to progress max
            maxBudgetDisplayText.text = "$$userBudget"
            progressBar.max = userBudget

            // find user spent entered
            val userSpent = budgetSpent.text.toString().toInt()
            // add spent to progress bar
            progressBar.progress = userSpent
            // add spent to display text
            spentPercentText.text = "Spent this month: $$userSpent"

            // show add button again
            addBudgetBtn.visibility = View.VISIBLE
            progressBar.visibility = View.VISIBLE

        }
    }
}

