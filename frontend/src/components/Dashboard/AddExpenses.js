import { Card, CardContent, Button, Typography, Box } from '@mui/material';
import AddCircleIcon from '@mui/icons-material/AddCircle';
import AccountBalanceWalletIcon from '@mui/icons-material/AccountBalanceWallet';

function AddExpenseCard({ handleOpen }) {
  return (
    <Card
      variant="outlined"
      sx={{
        width: 160,
        height: 160,
        borderRadius: 2,
        boxShadow: 2,
        display: 'flex',
        alignItems: 'center',
        justifyContent: 'center',
        p: 1, // padding around the content
      }}
    >
      <CardContent
        sx={{
          p: 0,
          width: '100%',
          height: '100%',
          display: 'flex',
          flexDirection: 'column',
          alignItems: 'center',
          justifyContent: 'space-between', // evenly space icon, label, button
        }}
      >
        {/* Icon with top margin */}
        <Box sx={{ mt: 1 }}>
          <AccountBalanceWalletIcon sx={{ fontSize: 40, color: 'primary.main' }} />
        </Box>

        {/* Label */}
        <Typography variant="subtitle1" fontWeight="bold">
          New Expense
        </Typography>

        {/* Add Button */}
        <Button
          variant="contained"
          color="primary"
          startIcon={<AddCircleIcon />}
          sx={{
            borderRadius: 2,
            px: 2,
            py: 1,
            fontWeight: 'bold',
            textTransform: 'none',
          }}
          onClick={handleOpen}
        >
          Add
        </Button>
      </CardContent>
    </Card>
  );
}

export default AddExpenseCard;
