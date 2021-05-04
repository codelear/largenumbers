import { Container } from "react-bootstrap";
import {} from "../css/style.css";

function ExpenseChart(props) {
  function CreateChartBar(expense, maxAmount) {
    const barHeight = Math.round((+expense.amount / maxAmount) * 100) + "%";
    return (
      <div className="chartbar">
        <div className="chartfill" style={{ height: barHeight }}></div>
      </div>
    );
  }

  const amounts = props.expenseItemsList.map((expense) => expense.amount);
  const maxAmount = Math.max(...amounts);
  if (props.expenseItemsList.length > 0) {
    return (
      <Container key="charcontainer">
        <div className="row m-3 p-3 bg-warning text-black rounded expense_filter justify-content-between">
          <div className="col-sm">
            <div className="chart">
              {props.expenseItemsList.map((expense) => {
                return CreateChartBar(expense, maxAmount);
              })}
            </div>
          </div>
        </div>
      </Container>
    );
  }
  return null;
}

export default ExpenseChart;
