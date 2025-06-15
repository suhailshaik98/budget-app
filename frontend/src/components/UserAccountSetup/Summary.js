import React, { useState, useEffect } from 'react';
import { Box, Button, Grid, Typography } from '@mui/material';
import AccountSummary from './AccountSummary';
import CategorySummary from './CategorySummary'; // Or CategoryBox if you want

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
  const handleSubmit = () => {
    // You can submit data to backend here or proceed to next step
    alert('Submitted!');
    // Optionally clear storage or navigate
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
