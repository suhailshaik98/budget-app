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
const Item = styled(Paper)(({ theme }) => ({
    backgroundColor: '#fff',
    ...theme.typography.body2,
    padding: theme.spacing(1),
    textAlign: 'center',
    color: (theme.vars ?? theme).palette.text.secondary,
    ...theme.applyStyles('dark', {
      backgroundColor: '#1A2027',
    }),
  }));
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
  <table>
                    <thead>
                        <tr>
                            <th>Header 1</th>
                            <th>Header 2</th>
                            <th>Header 3</th>
                            <th>
                                <Button variant="contained" size="small" startIcon={<AddCircleIcon />} onClick={handleOpen}>Add</Button>
                            </th>
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
