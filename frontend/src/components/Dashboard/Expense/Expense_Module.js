import React, { useEffect, useState } from "react";
import {
  Dialog, DialogTitle, DialogContent, DialogContentText, DialogActions,
  TextField, Button, Box, InputAdornment, MenuItem, Select, FormControl, InputLabel
} from "@mui/material";
import ArrowForwardIosIcon from '@mui/icons-material/ArrowForwardIos';

const apiUrl = "localhost"; // Or set this via props/environment

export default function Add_Expense({ open, onClose }) {
  const [accounts, setAccounts] = useState([]);
  const [selectedAccount, setSelectedAccount] = useState('');

  // Fetch accounts on dialog open
  useEffect(() => {
    if (open) {
      fetch(`http://${apiUrl}:18080/accounts?user_id=1`)
        .then(res => res.json())
        .then(data => setAccounts(data))
        .catch(err => console.error("Failed to fetch accounts:", err));
    }
  }, [open]);

  return (
    <Dialog
      open={open}
      onClose={onClose}
      slotProps={{
        paper: {
          component: 'form',
          onSubmit: async (event) => {
            event.preventDefault();
            const formData = new FormData(event.currentTarget);
            const formJson = Object.fromEntries(formData.entries());
            formJson.user_id = 1;

            try {
              const response = await fetch(`http://${apiUrl}:18080/add-transaction`, {
                method: "POST",
                headers: { "Content-Type": "application/json" },
                body: JSON.stringify(formJson)
              });

              if (!response.ok) {
                const text = await response.text();
                alert(`Submission failed: ${text}`);
                return;
              }

              const resultText = await response.text();
              alert(`Submission successful!\n\n${resultText}`);
            } catch (err) {
              console.error("Error submitting data:", err);
              alert("An error occurred while submitting.");
            }

            console.log('Submitted Expense:', formJson);
            onClose();
          }
        }
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
            name="transaction_name"
            label="Name of Transaction"
            type="text"
            fullWidth
            variant="standard"
          />

          <FormControl fullWidth margin="dense" variant="standard" required>
            <InputLabel id="account-label">Account</InputLabel>
            <Select
              labelId="account-label"
              id="account_name"
              name="account_name"
              value={selectedAccount}
              onChange={(e) => setSelectedAccount(e.target.value)}
            >
              {accounts.map((acc) => (
                <MenuItem key={acc.account_id} value={acc.account_name}>
                  {acc.account_name}
                </MenuItem>
              ))}
            </Select>
          </FormControl>

          <TextField
            required
            margin="dense"
            id="category"
            name="category"
            label="Category of Transaction"
            type="text"
            fullWidth
            variant="standard"
          />

          <TextField
            required
            margin="dense"
            id="date_of_transaction"
            name="date_of_transaction"
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
            name="amount"
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
