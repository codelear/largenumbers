import Button from "react-bootstrap/Button";
import Container from "react-bootstrap/Container";
import ExpenseDate from "./ExpenseDate";

const ExpenseItem = (props) => {
  return (
    <Container id={props.id}>
      <div className="row m-3 p-3 bg-warning text-black rounded expense_item">
        <div className="col-sm-3 col-4 expense_date bg-primary text-white border border-white rounded">
          <ExpenseDate date={props.date}></ExpenseDate>
        </div>
        <div className="col-sm-6 col-3 expense_description ">{props.title}</div>
        <div className="col-sm-3 col-5 expense_price">
          <Button variant="success" disabled block>
            ${props.amount}
          </Button>
        </div>
      </div>
    </Container>
  );
};

export default ExpenseItem;
