import { Outlet, useLocation, useNavigate } from "react-router-dom";
import TransactionTable from './TransactionTable';
import {
  Button,
  Box,
  Typography,
  Grid,
  Card,
  CardContent,
} from '@mui/material';
import Add_Expense from "./Expense/Expense_Module";
import React, { useEffect, useState } from "react";
import ButtonAppBar from "../TopBar/ButtonAppBar";
import AddCircleIcon from '@mui/icons-material/AddCircle';
import AddExpenseCard from "./AddExpenses";
function HomePageLayout() {
  const navigate = useNavigate();
  const location = useLocation();
  console.log(window.location.hostname);
  var apiUrl = window.location.hostname;

  const [openExpenseDialog, setOpenExpenseDialog] = useState(false);
  const [Transactions, setTransactions] = useState([]);

  const handleadddict = (newdictionary) => {
    setTransactions((previouslist) => [...previouslist, newdictionary]);
  };

  const handleOpen = () => setOpenExpenseDialog(true);
  const handleClose = () => setOpenExpenseDialog(false);

  const exampleTransactions = [
    { transaction_name: 'Groceries', account_name: 'Savings', category_name: 'Food', date_of_transaction: '2025-06-25', budgetItem: 'Grocery', amount: '45.05' },
    { transaction_name: 'Netflix', account_name: 'Checkings', category_name: 'Entertainment', date_of_transaction: '2025-06-20', budgetItem: 'Personal Use', amount: '25' },
  ];

  const getTransactionsPast30Days = async () => {
    try {
      let todays_date = new Date();
      let past_date = new Date(todays_date);
      const todays_date_format = todays_date.toISOString().split('T')[0]
      
      past_date.setDate(past_date.getDate() - 30);
      const past_date_format = past_date.toISOString().split('T')[0]

      console.log("Todays date: ", todays_date_format);
      console.log("Past date: ", past_date_format);

      const response = await fetch(`http://${apiUrl}:18080/get_transactions_timed/1/${past_date_format}_${todays_date_format}`);
      if (!response.ok) {
        throw new Error('Network response was not ok');
      }
      const data = await response.json();
      console.log("Fetched transactions:", data);
      if (data.data != null){
      setTransactions(data.data);

      }
    } catch (error) {
      console.error('Error fetching transactions:', error);
    }
  }

  useEffect(() => {
    getTransactionsPast30Days();
    // for (var i = 0; i < exampleTransactions.length; i++) {
    //   handleadddict(exampleTransactions[i]);
    // }
  }, []);

  return (
    <div>
      <ButtonAppBar />

      <Grid container spacing={2} sx={{ padding: 2 }}>
        
        {/* Transaction Table */}
        <Grid item xs={12} md={6}>
          <Box
            sx={{
              display: 'flex',
              alignItems: 'center',
              mb: 2,
              width: 800,
              maxWidth: '100%',
            }}
          >
            <TransactionTable transactions={Transactions} />
          </Box>
        </Grid>

        {/* Small Custom Card with Big Button */}
        <Grid item xs={12} md={6}>
          <Box
            sx={{
              display: 'flex',
              alignItems: 'center',
              mb: 2,
              width: 400,
              maxWidth: '100%',
            }}
          >
<AddExpenseCard handleOpen={handleOpen} />
          </Box>
        </Grid>

      </Grid>

      {/* Add Expense Dialog */}
      <Add_Expense open={openExpenseDialog} onClose={handleClose} addexpense={handleadddict} />
    </div>
  );
}

export default HomePageLayout;
