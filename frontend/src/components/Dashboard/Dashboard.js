import { Outlet, useLocation, useNavigate } from "react-router-dom";
import TransactionTable from './TransactionTable';
import {
  TextField,
  Button,
  Box,
  Typography,
  IconButton,
  Divider,
  Grid,
  Paper,
} from '@mui/material';
import { styled } from '@mui/material/styles';
import AddCircleIcon from '@mui/icons-material/AddCircle';
import Add_Expense from "./Expense/Expense_Module";
import React, { useEffect, useState } from "react";
import ButtonAppBar from "../TopBar/ButtonAppBar";

function HomePageLayout() {
  const navigate = useNavigate();
  const location = useLocation();
  console.log(window.location.hostname); // e.g., "example.com" or "192.168.1.10"
  var apiUrl = window.location.hostname; // Default to localhost for development from
  const [openExpenseDialog, setOpenExpenseDialog] = useState(false);
  const [Transactions, setTransactions] = useState([]);
  const handleadddict = (newdictionary) => {
  setTransactions((previouslist) => [...previouslist,newdictionary]) 
  }
  const handleOpen = () => setOpenExpenseDialog(true);
  const handleClose = () => setOpenExpenseDialog(false);
  const exampleTransactions = [
    { transaction_name: 'Groceries', account_name: 'Savings', category: 'Food', date_of_transaction: '2025-06-25', budgetItem: 'Grocery', amount: '45.05' },
    { transaction_name: 'Netflix', account_name: 'Checkings', category: 'Entertainment', date_of_transaction: '2025-06-20', budgetItem: 'Personal Use', amount: '25' },
  ];
  useEffect(() => {
  for (var i=0;i<exampleTransactions.length;i++)
  {
    handleadddict(exampleTransactions[i])}},[])
return (
    <div>
        <ButtonAppBar />
        <Grid container rowSpacing={1} columnSpacing={{ xs: 2, sm: 3, md: 4 }} sx={{ padding: 2 }}>
        {/* <Grid size={1} sx={{ padding: 2 }}>
    <Item>2</Item>
  </Grid>
  <Grid size={8} sx={{ padding: 2 }}>
    <Item>1</Item>
  </Grid>
  <Grid size={2} sx={{ padding: 2 }}>
    <Item>2</Item>
  </Grid> */}

  <Grid size={11} sx={{ padding: 2,display: 'flex', justifyContent: 'center'}}>
  <Button variant="contained" size="small" startIcon={<AddCircleIcon />} onClick={handleOpen}>Add</Button>
 
  </Grid>
  <Grid item xs={12}>
          <TransactionTable transactions={Transactions} />
        </Grid>
  {/* <Grid size={1} sx={{ padding: 2 }}>
    <Item>2</Item>
  </Grid> */}

  </Grid>
  <Add_Expense open={openExpenseDialog} onClose={handleClose} addexpense={handleadddict} />

    </div>
);
}

export default HomePageLayout;
