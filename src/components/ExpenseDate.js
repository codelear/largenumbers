
const ExpenseDate = (props) => {
  const month = props.date.toLocaleString("en-US", { month: "long" });
  const year = props.date.toLocaleString("en-US", { day: "2-digit" });
  const date = props.date.getFullYear();
  return (
    <div className="row ">
      <div className="col-sm pt-lg-2 pt-0">{year}</div>
      <div className="col-sm pt-lg-2 pt-0">{month}</div>
      <div className="col-sm pt-lg-2 pt-0">{date}</div>
    </div>
  );
};

export default ExpenseDate;
