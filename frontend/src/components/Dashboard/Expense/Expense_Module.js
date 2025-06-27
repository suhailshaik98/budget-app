import * as React from 'react';
import Button from '@mui/material/Button';
import TextField from '@mui/material/TextField';
import Dialog from '@mui/material/Dialog';
import DialogActions from '@mui/material/DialogActions';
import DialogContent from '@mui/material/DialogContent';
import DialogContentText from '@mui/material/DialogContentText';
import DialogTitle from '@mui/material/DialogTitle';
import InputAdornment from '@mui/material/InputAdornment';
import ArrowForwardIosIcon from '@mui/icons-material/ArrowForwardIos';
import Box from '@mui/material/Box';

export default function Add_Expense({ open, onClose, addexpense }) {
  return (
    <Dialog
      open={open}
      onClose={onClose}
      slotProps={{
        paper: {
          component: 'form',
          onSubmit: (event) => {
            event.preventDefault();
            const formData = new FormData(event.currentTarget);
            const formJson = Object.fromEntries(formData.entries());
            addexpense(formJson)
            console.log('Submitted Expense:', formJson);  // ✅ Print all fields
            onClose();
          },
        },
      }}
    >
      <DialogTitle>Add expense</DialogTitle>
      <DialogContent>
        <DialogContentText>
          Please enter the expense details here
        </DialogContentText>

        <Box sx={{ '& > :not(style)': { m: 1 } }}>
          <TextField
            autoFocus
            required
            margin="dense"
            id="transaction_name"
            name="transaction_name" // ✅ fixed
            label="Name of Transaction"
            type="text"
            fullWidth
            variant="standard"
          />

          <TextField
            required
            margin="dense"
            id="account_name"
            name="account_name" // ✅ fixed
            label="Account Name"
            type="text"
            fullWidth
            variant="standard"
          />

          <TextField
            required
            margin="dense"
            id="category"
            name="category" // ✅ fixed
            label="Category of Transaction"
            type="text"
            fullWidth
            variant="standard"
          />

          <TextField
            required
            margin="dense"
            id="date_of_transaction"
            name="date_of_transaction" // ✅ fixed
            label="Date of Transaction"
            type="date"
            fullWidth
            InputLabelProps={{ shrink: true }}
            variant="outlined"
            InputProps={{
              startAdornment: (
                <InputAdornment position="start">
                  <ArrowForwardIosIcon />
                </InputAdornment>
              ),
            }}
          />

          <TextField
            required
            margin="dense"
            id="amount"
            name="amount" // ✅ fixed
            label="Amount"
            type="number"
            fullWidth
            variant="standard"
          />
        </Box>
      </DialogContent>
      <DialogActions>
        <Button onClick={onClose}>Cancel</Button>
        <Button type="submit">Save Transaction</Button>
      </DialogActions>
    </Dialog>
  );
}
