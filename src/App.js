import { useState } from "react";
import ExpenseDisplay from "./components/ExpenseDisplay";
import ExpenseFilter from "./components/ExpenseFilter";
import NewExpenseItem from "./components/forms/NewExpenseItem";
import filterDataSet from "./components/FilterDataSet.js";
import ExpenseChart from "./components/ExpenseChart";

function App() {
  // prefill with some dummy expenses
  let expenses = [
    {
      title: "Car Insurance",
      amount: 234.5,
      date: new Date(2021, 2, 20),
      id: 0,
    },
    { title: "New TV", amount: 790.0, date: new Date(2021, 1, 14), id: 1 },
    { title: "Toilet Paper", amount: 8.5, date: new Date(2021, 2, 2), id: 3 },
  ];

  // states for expenses, filtered expenses based on the filter year and the filter year
  const [expenseItemsList, setExpenseItemsList] = useState([...expenses]);
  const [filteredExpenseItemsList, setFilteredExpenseItemsList] = useState([
    ...expenses,
  ]);
  const [filterYear, setFilterYear] = useState("All");

  // when getting a new expense, add the new expense to the state
  // the exisitng filtered expenses must also be updated to reflect the new expense in the display, 
  // incase the new expense is added in the same year as the current filter year
  function newExpenseItemHandler(expenseItem) {
    setExpenseItemsList((prevItems) => [
      ...prevItems,
      {
        title: expenseItem.title,
        amount: +expenseItem.amount,
        date: expenseItem.date,
        id: expenseItem.id,
      },
    ]);

    let dataset = filterDataSet(filterYear, [
      ...filteredExpenseItemsList,
      expenseItem,
    ]);
    setFilteredExpenseItemsList([...dataset]);
  }

  // when the year is changed then update the filtered expense based on year
  function filterHandler(year) {
    setFilterYear(year);
    let dataset = filterDataSet(year, expenseItemsList);
    setFilteredExpenseItemsList([...dataset]);
  }

  return (
    <div>
      <h2 className="text-center">React Expenses</h2>

      <NewExpenseItem onNewExpenseItem={newExpenseItemHandler}></NewExpenseItem>

      <ExpenseFilter onFilter={filterHandler}></ExpenseFilter>

      <ExpenseChart expenseItemsList={filteredExpenseItemsList}></ExpenseChart>

      <ExpenseDisplay
        expenseItemsList={filteredExpenseItemsList}
      ></ExpenseDisplay>
    </div>
  );
}

export default App;
