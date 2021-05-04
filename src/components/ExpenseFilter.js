import { useState } from "react";
import { Container, Dropdown } from "react-bootstrap";

function ExpenseFilter(props) {
const [inputYearFilter, setInputYearFilter] = useState("All");

// keep the year in state so that the drop down can reflect the selected year
  const yearChangeHandler = (eventArgs) =>
  {
    setInputYearFilter(eventArgs);
    props.onFilter(eventArgs);
  };

  return (
    <Container>
      <div className="row m-3 p-3 bg-warning text-black rounded expense_filter justify-content-between">
        <div className="col-sm-3 col-6"> Filter Year</div>
        <div className="col-sm-2 col-3 offset-sm-7">
          <Dropdown onSelect={yearChangeHandler}>
            <Dropdown.Toggle variant="info" id="dropdown-basic" title={inputYearFilter} >
              {inputYearFilter}
            </Dropdown.Toggle>

            <Dropdown.Menu >
            <Dropdown.Item eventKey="All">All</Dropdown.Item>
              <Dropdown.Item eventKey="2019">2019</Dropdown.Item>
              <Dropdown.Item eventKey="2020">2020</Dropdown.Item>
              <Dropdown.Item eventKey="2021">2021</Dropdown.Item>
            </Dropdown.Menu>
          </Dropdown>

        </div>
      </div>
    </Container>
  );
}

export default ExpenseFilter;
