import React from "react";
import Add_Expense from "../Expense/Expense_Module";
console.log(window.location.hostname); // e.g., "example.com" or "192.168.1.10"
var apiUrl = window.location.hostname; // Default to localhost for developmen
// Example API call (not used in the component)
fetch('http://${apiUrl}:18080/get_transactions_timed/1/2025-05-04_2025-06-05')
    .then(response => response.json())
    .then(data => {
        // handle data if needed
    })
    .catch(error => {
        // handle error if needed
    });

const RecentTransactionsTable = () => (
        <div>
                <Add_Expense/>
    <table>
            <thead>
                    <tr>
                            <th></th>
                            <th></th>
                            <th></th>
                    </tr>
                                        <tr>
                            <th></th>
                            <th></th>
                            <th></th>
                    </tr>
                    <tr>
                            <th>Header 1</th>
                            <th>Header 2</th>
                            <th>Header 3</th>
                    </tr>
            </thead>
            <tbody>
                    <tr>
                            <td>Row 1, Cell 1</td>
                            <td>Row 1, Cell 2</td>
                            <td>Row 1, Cell 3</td>
                    </tr>
                    <tr>
                            <td>Row 2, Cell 1</td>
                            <td>Row 2, Cell 2</td>
                            <td>Row 2, Cell 3</td>
                    </tr>
            </tbody>
    </table>
        </div>

);

export default RecentTransactionsTable;
