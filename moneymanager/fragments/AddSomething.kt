package com.example.moneymanager.fragments

import android.icu.util.Calendar
import android.os.Build
import android.os.Bundle
import android.view.*
import android.widget.*
import androidx.annotation.RequiresApi
import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentTransaction
import androidx.fragment.app.activityViewModels
import com.example.moneymanager.R
import com.example.moneymanager.datamodels.MoneyInfo
import com.example.moneymanager.viewmodels.MoneyViewModel
import kotlinx.android.synthetic.main.fragment_add_something.*

class AddSomething : Fragment() {

    private val moneyViewModel : MoneyViewModel by activityViewModels()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_add_something, container, false)
    }

    @RequiresApi(Build.VERSION_CODES.N)
    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        val doneBtn = view.findViewById(R.id.doneButton) as Button

        doneBtn.setOnClickListener {
            Toast.makeText(activity, "Added!", Toast.LENGTH_SHORT).show()
            saveMoney(moneyDescInputField, moneyAmountInputField, moneyTypeInputField, moneyDateInputField)
            val frag = AllMoney()
            val fragMgr = requireActivity().supportFragmentManager
            fragMgr.beginTransaction()
                .replace(R.id.fragment, frag)
                .setTransition(FragmentTransaction.TRANSIT_FRAGMENT_OPEN)
                .commit()
        }

        // all buttons
        val expenseBtn = view.findViewById(R.id.expenseButton) as Button
        val incomeBtn = view.findViewById(R.id.incomeButton) as Button
        val receiptBtn = view.findViewById(R.id.receiptButton) as Button
        val weeklyBtn = view.findViewById(R.id.weeklyButton) as Button
        val monthlyBtn = view.findViewById(R.id.monthlyButton) as Button
        val yearlyBtn = view.findViewById(R.id.yearlyButton) as Button

        // find date of money text box
        val moneyDateTextBox = view.findViewById(R.id.moneyDateInputField) as TextView
        // find type of money text box
        val moneyTypeTextBox = view.findViewById(R.id.moneyTypeInputField) as TextView

        // find date picker
        val datePicker = view.findViewById<DatePicker>(R.id.datePicker)
        // get current date
        val c = Calendar.getInstance()

        // activate date picker
        datePicker.init(c.get(Calendar.YEAR), c.get(Calendar.MONTH),
            c.get(Calendar.DAY_OF_MONTH)

        // set date picker to date user selects
        ) { view, year, month, day ->
            val month = month + 1
            // display date that user selects in text box
            moneyDateTextBox.text = "$month/$day/$year"
        }

        //switch
        val repeatSwitch = view.findViewById(R.id.repeatSwitch) as Switch

        // select weekly, monthly, or yearly buttons
        weeklyBtn.visibility = View.INVISIBLE
        monthlyBtn.visibility = View.INVISIBLE
        yearlyBtn.visibility = View.INVISIBLE

        // set listener for repeat switch
        repeatSwitch.setOnCheckedChangeListener { buttonView, isChecked ->
            if(isChecked){
                // make buttons visible
                weeklyBtn.visibility = View.VISIBLE
                monthlyBtn.visibility = View.VISIBLE
                yearlyBtn.visibility = View.VISIBLE
                weeklyBtn.setOnClickListener {
                    Toast.makeText(activity, "Repeat Weekly", Toast.LENGTH_SHORT).show()
                }
                monthlyBtn.setOnClickListener {
                    Toast.makeText(activity, "Repeat Monthly", Toast.LENGTH_SHORT).show()
                }
                yearlyBtn.setOnClickListener {
                    Toast.makeText(activity, "Repeat Yearly", Toast.LENGTH_SHORT).show()
                }
            }
            else{
                // make buttons invisible
                weeklyBtn.visibility = View.INVISIBLE
                monthlyBtn.visibility = View.INVISIBLE
                yearlyBtn.visibility = View.INVISIBLE
            }
        }
        // Income button clicked
        incomeBtn.setOnClickListener {
            Toast.makeText(activity, "Adding Income", Toast.LENGTH_SHORT).show()
            moneyTypeTextBox.text = "Income"

        }

        // Expense button clicked
        expenseBtn.setOnClickListener {
            Toast.makeText(activity, "Adding Expense", Toast.LENGTH_SHORT).show()
            moneyTypeTextBox.text = "Expense"
        }

        // Receipt button clicked
        receiptBtn.setOnClickListener {
            repeatSwitch.visibility = View.INVISIBLE

            Toast.makeText(activity, "ACCESS TO CAMERA NEEDED", Toast.LENGTH_LONG).show()
        }
    }

    private fun saveMoney(
        moneyDescInputField: TextView, moneyAmountInputField: TextView,
        moneyTypeInputField: TextView, moneyDateInputField: TextView
    ) {
        val moneyDesc : String = moneyDescInputField.text.toString()
        val moneyAmount : String = moneyAmountInputField.text.toString()
        val moneyType : String = moneyTypeInputField.text.toString()
        val moneyDate : String = moneyDateInputField.text.toString()

        val money = MoneyInfo(moneyDesc, moneyAmount, moneyType, moneyDate)
        moneyViewModel.addMoney(money)
    }
}

