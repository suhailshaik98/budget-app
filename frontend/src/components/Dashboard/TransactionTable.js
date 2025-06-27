import React from 'react';
import {
  Table, TableBody, TableCell, TableContainer,
  TableHead, TableRow, Paper, Typography
} from '@mui/material';

const TransactionTable = ({ transactions = [] }) => {
  return (
    <TableContainer component={Paper}>
      <Typography variant="h6" sx={{ p: 2 }}>
        Recent Transactions
      </Typography>
      <Table>
        <TableHead>
          <TableRow>
            <TableCell>Name</TableCell>
            <TableCell>Account Name</TableCell>
            <TableCell>Category</TableCell>
            <TableCell>Date</TableCell>
            {/* <TableCell>Budget Item</TableCell> */}
            <TableCell>Amount($)</TableCell>
          </TableRow>
        </TableHead>
        <TableBody>
          {transactions.length === 0 ? (
            <TableRow>
              <TableCell colSpan={5} align="center">No transactions available</TableCell>
            </TableRow>
          ) : (
            transactions.map((txn, index) => (
              <TableRow key={index}>
                <TableCell>{txn.transaction_name}</TableCell>
                <TableCell>{txn.account_name}</TableCell>
                <TableCell>{txn.category}</TableCell>
                <TableCell>{txn.date_of_transaction}</TableCell>
                {/* <TableCell>{txn.budgetItem}</TableCell> */}
                <TableCell>{txn.amount}</TableCell>
              </TableRow>
            ))
          )}
        </TableBody>
      </Table>
    </TableContainer>
  );
};

export default TransactionTable;