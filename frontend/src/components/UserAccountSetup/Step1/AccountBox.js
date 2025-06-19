import React from 'react';
import { Box, TextField, Typography, IconButton,FormControl,MenuItem,Select,InputLabel } from '@mui/material';
import { Delete } from '@mui/icons-material';

const AccountBox = ({ account, index, onChange, onRemove, canDelete, errors }) => {
  const handleFieldChange = (field, value) => {
    onChange(field, value);
  };

  return (
    <Box sx={{ mb: 3, p: 2, border: '1px solid #ccc', borderRadius: 2, maxWidth: 300 }}>
      <Typography variant="subtitle1">Account {index !== undefined ? index + 1 : ''}</Typography>

      <TextField
        label="Account Name"
        value={account.account_name}
        onChange={(e) => handleFieldChange('account_name', e.target.value)}
        fullWidth
        margin="normal"
        required
        error={errors?.account_name}
        helperText={errors?.account_name ? 'Please enter account name' : ''}
      />
<FormControl fullWidth>
  <InputLabel id="demo-simple-select-label">Account</InputLabel>
  <Select
    labelId="demo-simple-select-label"
    id="demo-simple-select"
    value={account.account_type}
    label="Account"
    required
    error={errors?.account_type}
    helperText={errors?.account_type ? 'Please enter account type' : ''}
    onChange={(e) => handleFieldChange('account_type', e.target.value)}
    >
    <MenuItem value={"Savings"}>Savings</MenuItem>
    <MenuItem value={"Checkings"}>Checkings</MenuItem>
    <MenuItem value={"Credit Card"}>Credit Card</MenuItem>
  </Select>
</FormControl>
      {/* <TextField
        label="Account Type"
        value={account.account_type}
        onChange={(e) => handleFieldChange('account_type', e.target.value)}
        fullWidth
        margin="normal"
        required
        error={errors?.account_type}
        helperText={errors?.account_type ? 'Please enter account type' : ''}
      /> */}

      <TextField
        label="Balance"
        type="number"
        value={account.balance}
        onChange={(e) => handleFieldChange('balance', e.target.value)}
        fullWidth
        margin="normal"
        required
        error={errors?.balance}
        helperText={errors?.balance ? 'Please enter a valid balance' : ''}
      />

      {canDelete && (
        <IconButton onClick={() => onRemove(index)} color="error" sx={{ mt: 1 }}>
          <Delete />
        </IconButton>
      )}
    </Box>
  );
};

export default AccountBox;
