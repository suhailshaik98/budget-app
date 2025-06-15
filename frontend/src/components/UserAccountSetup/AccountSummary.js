import React from 'react';
import {
  Accordion,
  AccordionSummary,
  AccordionDetails,
  AccordionActions,
  Typography,
  IconButton,
  Button,
  Box
} from '@mui/material';
import { Delete, ExpandMore } from '@mui/icons-material';

const AccountSummary = ({ accounts, onDelete }) => {
  return (
    <Box sx={{ mt: 4 }}>


      {accounts.map((acc, index) => (
        <Accordion key={index} sx={{ my: 1 }}>
          <AccordionSummary
            expandIcon={<ExpandMore />}
            aria-controls={`panel${index + 1}-content`}
            id={`panel${index + 1}-header`}
          >
            <Typography component="span">
              Account {index + 1}: {acc.account_name}
            </Typography>
          </AccordionSummary>

          <AccordionDetails>
            <Typography><strong>Type:</strong> {acc.account_type}</Typography>
            <Typography><strong>Balance:</strong> ${acc.balance}</Typography>
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

export default AccountSummary;
