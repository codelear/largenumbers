import Form from "react-bootstrap/Form";
import Button from "react-bootstrap/Button";
import { Container, Modal } from "react-bootstrap";
import React, { useState } from "react";

function NewExpenseItem(props) {
  const [inputExpenseTitle, setInputExpenseTitle] = useState("");
  const [inputExpenseAmount, setInputExpenseAmount] = useState("");
  const [inputExpenseDate, setInputExpenseDate] = useState("");
  const [showModal, setShowModal] = useState(false);

  const clearForm = () => {
    setInputExpenseTitle("");
    setInputExpenseAmount("");
    setInputExpenseDate("");
  }

  const newItemCreateSubmittedHandler = (eventArgs) => {
    eventArgs.preventDefault();
    setShowModal(false);
    const expenseData = {
      title: inputExpenseTitle,
      amount: +inputExpenseAmount,
      date: inputExpenseDate,
      id: Date.UTC()
    };
    clearForm();
    props.onNewExpenseItem(expenseData);
  };

  const titleChangedHandler = (eventArgs) => {
    setInputExpenseTitle(eventArgs.target.value);
  };

  const dateChangedHandler = (eventArgs) => {
    setInputExpenseDate(eventArgs.target.valueAsDate);
  };

  const amountChangedHandler = (eventArgs) => {
    setInputExpenseAmount(eventArgs.target.value);
  };

  const showHandler = () => setShowModal(true);
  const closeHandler = (args) => {
    setShowModal(false);
    clearForm();
  };

  // form shown inside modal window
  return (
    <Container>
      <div className="row m-3 p-3 bg-primary new_expense_item justify-content-center">
        <div className="col-sm p-2 expense_date bg-info border border-white rounded justify-content-center text-center">
          <Button variant="primary" onClick={showHandler}>
            New Expense
          </Button>

          <Modal show={showModal} onHide={closeHandler}>
            <Modal.Header closeButton>
              <Modal.Title>Add New Expense Details</Modal.Title>
            </Modal.Header>

            <Modal.Body>
              <Form onSubmit={newItemCreateSubmittedHandler} name="expenseform">
                <Form.Group controlId="formBasicTitle">
                  <Form.Label>Expense Title</Form.Label>
                  <Form.Control
                    required
                    type="text"
                    placeholder="Enter expense title"
                    onChange={titleChangedHandler}
                    value={inputExpenseTitle}
                  />
                </Form.Group>

                <Form.Group controlId="formBasicAmount">
                  <Form.Label>Expense Amount</Form.Label>
                  <Form.Control
                    required
                    type="number"
                    min="0.01"
                    step="0.01"
                    placeholder="Enter expense amount"
                    onChange={amountChangedHandler}
                    value={inputExpenseAmount}
                  />
                </Form.Group>

                <Form.Group controlId="formBasicDate">
                  <Form.Label>Expense Date</Form.Label>
                  <Form.Check
                    required
                    type="date"
                    label="Expense Date"
                    onChange={dateChangedHandler}
                    selected={inputExpenseDate}
                  />
                </Form.Group>

                <Modal.Footer>
                <Button variant="secondary" onClick={closeHandler}>
                  Close
                </Button>

                <Button variant="primary" type="submit">
                  Submit
                </Button>
                </Modal.Footer>
              </Form>
            </Modal.Body>
          </Modal>
        </div>
      </div>
    </Container>
  );
}

export default NewExpenseItem;
