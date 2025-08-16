import React, { useState, useEffect } from 'react';
import { Grid, Button, Typography } from '@mui/material';
import AccountBox from './AccountBox';
import AccountSummary from './AccountSummary';

const Step1 = () => {
  const [currentAccount, setCurrentAccount] = useState({
    account_name: '',
    account_type: '',
    balance: '',
  });

  const [savedAccounts, setSavedAccounts] = useState([]);

  const [errors, setErrors] = useState({
    account_name: false,
    account_type: false,
    balance: false,
  });

  // Load saved accounts from localStorage on mount
  useEffect(() => {
    const stored = localStorage.getItem('accounts');
    if (stored) {
      setSavedAccounts(JSON.parse(stored));
    }
  }, []);

  // Handle input change
  const handleAccountChange = (field, value) => {
    setCurrentAccount(prev => ({ ...prev, [field]: value }));
    setErrors(prev => ({ ...prev, [field]: false }));
  };

  // Validate input fields
  const validateCurrentAccount = () => {
    const newErrors = {
      account_name: currentAccount.account_name.trim() === '',
      account_type: currentAccount.account_type.trim() === '',
      balance: currentAccount.balance === '' || isNaN(currentAccount.balance),
    };
    setErrors(newErrors);
    return !Object.values(newErrors).some(Boolean);
  };

  // Add account and save to localStorage
  const handleAddAccount = () => {
    if (validateCurrentAccount()) {
      const updated = [...savedAccounts, currentAccount];
      setSavedAccounts(updated);
      localStorage.setItem('accounts', JSON.stringify(updated));
      setCurrentAccount({ account_name: '', account_type: '', balance: '' });
    }
  };

  // Remove and update localStorage
  const handleRemoveAccount = (index) => {
    const updated = savedAccounts.filter((_, i) => i !== index);
    setSavedAccounts(updated);
    localStorage.setItem('accounts', JSON.stringify(updated));
  };

  return (
    <Grid container spacing={2}>
      {/* Left: Account input form */}
      <Grid item xs={12} md={4}>
        <Typography variant="h6" gutterBottom>
          Add / Edit Account
        </Typography>
        <AccountBox
          account={currentAccount}
          onChange={handleAccountChange}
          canDelete={false}
          errors={errors}
        />
        <Button variant="outlined" onClick={handleAddAccount} fullWidth>
          Add Account
        </Button>
      </Grid>

      {/* Right: Saved account summaries */}
      <Grid item xs={12} md={8}>
        <Typography variant="h6" gutterBottom>
          Added Account Summary
        </Typography>
        {savedAccounts.length === 0 ? (
          <Typography>No accounts added yet.</Typography>
        ) : (
          <AccountSummary accounts={savedAccounts} onDelete={handleRemoveAccount} />
        )}
      </Grid>
    </Grid>
  );
};

export default Step1;
