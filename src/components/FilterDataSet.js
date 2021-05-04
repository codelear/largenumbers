// if the year is All the return the complete dataset
// else only the expenses that match the year
function filterDataSet(filterYear, dataSet) {
  if (filterYear !== "All") {
    let filteredData = dataSet.filter((expenseItem) => {
      return expenseItem.date.getFullYear().toString() === filterYear;
    });
    return filteredData;
  }
  return dataSet;
}

export default filterDataSet;
