import React, { useState, useEffect } from 'react';
import { Grid, Box, Button, Typography, TextField } from '@mui/material';
import CategorySummary from './CategorySummary';

const CategoryBox = ({ category, onChange }) => {
  const handleFieldChange = (field, value) => {
    onChange(field, value);
  };

  return (
    <Box sx={{ mb: 3, p: 2, border: '1px solid #ccc', borderRadius: 2, maxWidth: 300 }}>
      <Typography variant="subtitle1">Add Category</Typography>

      <TextField
        label="Category Name"
        value={category.category_name}
        onChange={(e) => handleFieldChange('category_name', e.target.value)}
        fullWidth
        margin="normal"
        required
      />

      <TextField
        label="Budget Amount"
        type="number"
        value={category.budget}
        onChange={(e) => handleFieldChange('budget', e.target.value)}
        fullWidth
        margin="normal"
        required
      />
    </Box>
  );
};

const Step2 = () => {
  const [currentCategory, setCurrentCategory] = useState({
    category_name: '',
    budget: '',
  });

  const [savedCategories, setSavedCategories] = useState([]);

  // Load categories from localStorage on mount
  useEffect(() => {
    const storedCategories = localStorage.getItem('categories');
    if (storedCategories) {
      setSavedCategories(JSON.parse(storedCategories));
    }
  }, []);

  const handleCategoryChange = (field, value) => {
    setCurrentCategory(prev => ({ ...prev, [field]: value }));
  };

  const handleAddCategory = () => {
    if (!currentCategory.category_name || !currentCategory.budget) {
      alert('Please fill in both category name and budget.');
      return;
    }

    const updated = [...savedCategories, currentCategory];
    setSavedCategories(updated);
    localStorage.setItem('categories', JSON.stringify(updated));
    setCurrentCategory({ category_name: '', budget: '' });
  };

  const handleRemoveCategory = (index) => {
    const updated = savedCategories.filter((_, i) => i !== index);
    setSavedCategories(updated);
    localStorage.setItem('categories', JSON.stringify(updated));
  };

  return (
    <Box>
      <Grid container spacing={2}>
        {/* Left: Category input form */}
        <Grid item xs={12} md={4}>
          <Typography variant="h6" gutterBottom>
            Give budget for each category
          </Typography>
          <CategoryBox
            category={currentCategory}
            onChange={handleCategoryChange}
          />
          <Button variant="outlined" onClick={handleAddCategory} fullWidth>
            Add Category
          </Button>
        </Grid>

        {/* Right: Saved categories summary */}
        <Grid item xs={12} md={7}>
          <Typography variant="h6" gutterBottom>
            Category-wise Budget
          </Typography>
          <CategorySummary
            categories={savedCategories}
            onDelete={handleRemoveCategory}
          />
        </Grid>
      </Grid>
    </Box>
  );
};

export default Step2;
