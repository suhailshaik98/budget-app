import React, { useState, useEffect } from 'react';
import { Box, Button, Grid, Typography } from '@mui/material';
import AccountSummary from './Step1/AccountSummary';
import CategorySummary from './Step2/CategorySummary'; // Or CategoryBox if you want
console.log(window.location.hostname); // e.g., "example.com" or "192.168.1.10"
var apiUrl = window.location.hostname; // Default to localhost for developmen
const Step3 = () => {
  const [accounts, setAccounts] = useState([]);
  const [categories, setCategories] = useState([]);

  // Load data from localStorage on mount
  useEffect(() => {
    const storedAccounts = localStorage.getItem('accounts');
    const storedCategories = localStorage.getItem('categories');
    
    if (storedAccounts) {
      setAccounts(JSON.parse(storedAccounts));
    }

    if (storedCategories) {
      setCategories(JSON.parse(storedCategories));
    }
  }, []);

  // Delete handlers
  const handleDeleteAccount = (index) => {
    const updated = accounts.filter((_, i) => i !== index);
    setAccounts(updated);
    localStorage.setItem('accounts', JSON.stringify(updated));
  };

  const handleDeleteCategory = (index) => {
    const updated = categories.filter((_, i) => i !== index);
    setCategories(updated);
    localStorage.setItem('categories', JSON.stringify(updated));
  };

  // Submit handler example
  const handleSubmit = async () => {
    const storedAccounts = localStorage.getItem('accounts');
    const storedCategories = localStorage.getItem('categories');
  
    const payload = {
      user_id: 1,
      accounts: storedAccounts ? JSON.parse(storedAccounts) : [],
      categories: storedCategories ? JSON.parse(storedCategories) : [],
    };
    console.log("Loading data from localStorage payload:", payload);
    try {
      const response = await fetch(`http://${apiUrl}:18080/setup-initial`, {
        method: "POST",
        headers: {
          "Content-Type": "application/json"
        },
        body: JSON.stringify(payload)
      });
  
      if (!response.ok) {
        const text = await response.text();
        alert(`Submission failed: ${text}`);
        return;
      }
  
      const resultText = await response.text();
      alert(`Submission successful!\n\n${resultText}`);
      // Optionally navigate or clear data
    } catch (err) {
      console.error("Error submitting data:", err);
      alert("An error occurred while submitting.");
    }
  };

  return (
    <Box sx={{ p: 3 }}>
      <Typography variant="h5" gutterBottom>
        Summary
      </Typography>

      <Grid container spacing={4}>
        <Grid item xs={12} md={6}>
          <Typography variant="h6" gutterBottom>
            Accounts
          </Typography>
          {accounts.length === 0 ? (
            <Typography>No accounts added yet.</Typography>
          ) : (
            <AccountSummary accounts={accounts} onDelete={handleDeleteAccount} />
          )}
        </Grid>

        <Grid item xs={12} md={6}>
          <Typography variant="h6" gutterBottom>
            Categories
          </Typography>
          {categories.length === 0 ? (
            <Typography>No categories added yet.</Typography>
          ) : (
            <CategorySummary categories={categories} onDelete={handleDeleteCategory} />
          )}
        </Grid>
      </Grid>

      <Box sx={{ mt: 4, textAlign: 'center' }}>
        <Button variant="contained" color="primary" onClick={handleSubmit}>
          Submit
        </Button>
      </Box>
    </Box>
  );
};

export default Step3;
