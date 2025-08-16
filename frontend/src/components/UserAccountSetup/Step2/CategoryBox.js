import React from 'react';
import { Box, Button, IconButton, TextField, Typography } from '@mui/material';
import DeleteIcon from '@mui/icons-material/Delete';

const CategoryBox = ({ category, onChange }) => {
  const handleCategoryNameChange = (value) => {
    onChange('category_name', value);
  };

  const handleItemChange = (index, field, value) => {
    const updatedItems = [...(category.budget_items || [])];
    updatedItems[index][field] = value;
    onChange('budget_items', updatedItems);
  };

  const handleAddItem = () => {
    const updatedItems = [...(category.budget_items || []), { name: '', amount: '' }];
    onChange('budget_items', updatedItems);
  };

  const handleRemoveItem = (index) => {
    const updatedItems = [...(category.budget_items || [])];
    updatedItems.splice(index, 1);
    onChange('budget_items', updatedItems);
  };

  return (
    <Box sx={{ mb: 3, p: 2, border: '1px solid #ccc', borderRadius: 2, maxWidth: 400 }}>
      <Typography variant="subtitle1" gutterBottom>
        Add Category
      </Typography>

      <TextField
        label="Category Name"
        value={category.category_name}
        onChange={(e) => handleCategoryNameChange(e.target.value)}
        fullWidth
        margin="normal"
        required
      />

      <Typography variant="subtitle2" sx={{ mt: 2 }}>
        Budget Items
      </Typography>

      {(category.budget_items || []).map((item, index) => (
        <Box key={index} sx={{ display: 'flex', gap: 1, mt: 1 }}>
          <TextField
            label="Item Name"
            value={item.name}
            onChange={(e) => handleItemChange(index, 'name', e.target.value)}
            fullWidth
          />
          <TextField
            label="Amount"
            type="number"
            value={item.amount}
            onChange={(e) => handleItemChange(index, 'amount', e.target.value)}
            sx={{ width: 100 }}
          />
          <IconButton onClick={() => handleRemoveItem(index)} color="error">
            <DeleteIcon />
          </IconButton>
        </Box>
      ))}

      <Box sx={{ textAlign: 'right', mt: 2 }}>
        <Button onClick={handleAddItem} variant="outlined" size="small">
          + Add Item
        </Button>
      </Box>
    </Box>
  );
};

export default CategoryBox;
