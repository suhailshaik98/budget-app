import React, { useState, useEffect } from 'react';
import { Grid, Box, Button, Typography, TextField } from '@mui/material';
import CategorySummary from './CategorySummary';
import CategoryBox from './CategoryBox';


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
    if (!currentCategory.category_name || !currentCategory.budget_items) {

      alert('Please fill in both category name and budget.');
      console.log(currentCategory)
      return;
    }
    const totalBudget = currentCategory.budget_items.reduce((sum, item) => {
      const amount = parseFloat(item.amount);
      return sum + (isNaN(amount) ? 0 : amount);
    }, 0);
    currentCategory.budget = totalBudget.toString();
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
