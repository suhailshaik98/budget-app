import React from 'react';
import {
  Accordion,
  AccordionSummary,
  AccordionDetails,
  AccordionActions,
  Typography,
  Button,
  Box,
} from '@mui/material';
import ExpandMoreIcon from '@mui/icons-material/ExpandMore';
import { Delete, ExpandMore } from '@mui/icons-material';

const CategorySummary = ({ categories, onDelete }) => {


      return (
        <Box sx={{ mt: 4 }}>
    
    
          {categories.map((acc, index) => (
            <Accordion key={index} sx={{ my: 1 }}>
              <AccordionSummary
                expandIcon={<ExpandMore />}
                aria-controls={`panel${index + 1}-content`}
                id={`panel${index + 1}-header`}
              >
                <Typography component="span">
                  {acc.category_name}
                </Typography>
              </AccordionSummary>
    
              <AccordionDetails>
                <Typography><strong>Category</strong> {acc.category_name}</Typography>
                <Typography><strong>Budget</strong> ${acc.budget}</Typography>
              </AccordionDetails>
    
              <AccordionActions>
                <Button
                  size="small"
                  color="error"
                  startIcon={<Delete />}
                  onClick={() => onDelete(index)}
                >
                  Delete
                </Button>
              </AccordionActions>
            </Accordion>
          ))}
        </Box>
      );
};

export default CategorySummary;
