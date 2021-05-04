import ExpenseItem from "./ExpenseItem";

function ExpenseDisplay(props) {

  return props.expenseItemsList.map((expense) => {
    return (
      CreateExpenseItemElement(expense)
    );
  });

    function CreateExpenseItemElement(expenseItem) {
        return <ExpenseItem
            title={expenseItem.title}
            amount={+expenseItem.amount}
            date={expenseItem.date} />;
    }
}

export default ExpenseDisplay;
