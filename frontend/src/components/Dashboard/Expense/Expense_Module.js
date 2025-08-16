import React, { useEffect, useState } from "react";
import {
  Dialog, DialogTitle, DialogContent, DialogContentText, DialogActions,
  TextField, Button, Box, InputAdornment, MenuItem, Select, FormControl, InputLabel
} from "@mui/material";
import ArrowForwardIosIcon from '@mui/icons-material/ArrowForwardIos';

console.log(window.location.hostname); // e.g., "example.com" or "192.168.1.10"
var apiUrl = window.location.hostname; // Default to localhost for developmen
export default function Add_Expense({ open, onClose, addexpense }) {
  const [accounts, setAccounts] = useState([]);
  const [categories, setCategories] = useState([]);
  const [selectedCategory, setSelectedCategory] = useState('');
  const [selectedAccount, setSelectedAccount] = useState('');

  // Fetch accounts on dialog open
  useEffect(() => {
    if (open) {
      fetch(`http://${apiUrl}:18080/accounts_info/1`)
        .then(res => res.json())
        .then(data => {
          console.log("Fetched accounts:", data);
          setAccounts(data.accounts);
        })
        .catch(err => console.error("Failed to fetch accounts:", err));
    }
  }, [open]);

    useEffect(() => {
    if (open) {
      fetch(`http://${apiUrl}:18080/categories_info/1`)
        .then(res => res.json())
        .then(data => {
          console.log("Fetched categories:", data);
          setCategories(data.budget_items);
        })
        .catch(err => console.error("Failed to fetch categories:", err));
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
            formJson.account_name = selectedAccount.split(" - ")[0];
            formJson.account_type = selectedAccount.split(" - ")[1];
            formJson.category_name = selectedCategory.split(" - ")[1];
            formJson.budget_item_name = selectedCategory.split(" - ")[0];
            addexpense (formJson); // Call the parent function to add the expense
            console.log('Form Data:', formJson);

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
                <MenuItem key={acc.account_id} value={acc.account_name  + " - " + acc.account_type}>
                  {acc.account_name+ " - " + acc.account_type}
                </MenuItem>
              ))}
            </Select>
          </FormControl>

          <FormControl fullWidth margin="dense" variant="standard" required>
            <InputLabel id="category-label">Category</InputLabel>
            <Select
              labelId="category-label"
              id="category_name"
              name="category_name"
              value={selectedCategory}
              onChange={(e) => setSelectedCategory(e.target.value)}
            >
              {categories.map((cat) => (
                <MenuItem key={cat.budget_items_id} value={cat.budget_item_name+ " - " + cat.category}>
                  {cat.budget_item_name} - {cat.category}
                </MenuItem>
              ))}
            </Select>
          </FormControl>

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
            inputProps={{
              step: "0.01",  // ✅ Allows decimal input like 10.99
              min: "0"       // Optional: Prevent negative amounts if you want
            }}
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