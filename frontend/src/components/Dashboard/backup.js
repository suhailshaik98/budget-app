import { Outlet, useLocation, useNavigate } from "react-router-dom";
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
import React, { useState } from "react";
import ButtonAppBar from "../TopBar/ButtonAppBar";
import RecentTransactionsTable from "./Transactions/RecentTransactions";

function HomePageLayout() {
  const navigate = useNavigate();
  const location = useLocation();
  console.log(window.location.hostname); // e.g., "example.com" or "192.168.1.10"
  var apiUrl = window.location.hostname; // Default to localhost for developmen
  const [openExpenseDialog, setOpenExpenseDialog] = useState(false);

  const handleOpen = () => setOpenExpenseDialog(true);
  const handleClose = () => setOpenExpenseDialog(false);
return (
    <div>
        <ButtonAppBar />
        <Grid container rowSpacing={1} columnSpacing={{ xs: 4, sm: 3, md: 4 }} sx={{ padding: 2 }}>
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
 <RecentTransactionsTable/>

  </Grid>
  {/* <Grid size={1} sx={{ padding: 2 }}>
    <Item>2</Item>
  </Grid> */}
  </Grid>
  <Add_Expense open={openExpenseDialog} onClose={handleClose} />

    </div>
);
}

export default HomePageLayout;
