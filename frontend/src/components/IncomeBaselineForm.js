import React, {useState} from 'react';
import {TextField, Button, Typography, Box} from '@mui/material'
console.log(window.location.hostname); // e.g., "example.com" or "192.168.1.10"
var apiUrl = window.location.hostname; // Default to localhost for developmen
function IncomeBaselineForm({onSubmit}){
    const [savings, setSavings] = useState('');
    const [checkings, setCheckings] = useState('');
    const handleSubmit = async (e) => {
        e.preventDefault();
        onSubmit({savings: parseFloat(savings),checkings:parseFloat(checkings)});
        try {
            console.log("Submitting data to:", `${apiUrl}`)
            const res = await fetch(`http://${apiUrl}:18080/set`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({savings: parseFloat(savings), checkings: parseFloat(checkings)}),
            });
            if (!res.ok) {
                throw new Error('Network response was not ok');
            }
        } catch (error) {
            console.error("Error during submission:", error);
        }
    }
    return (
        <Box sx={{maxWidth: 400, margin:'auto',mt:4}}>
            <Typography variant='h5' gutterBottom>
                Income Baseline
                </Typography>
            <form onSubmit={handleSubmit} noValidate>
                <TextField
                    label="Savings"
                    type="number"
                    fullWidth
                    margin="normal"
                    value={savings}
                    onChange={(e)=> setSavings(e.target.value)}
                    required/>
                <TextField
                    label="Checkings"
                    type="number"
                    fullWidth
                    margin="normal"
                    value={checkings}
                    onChange={(e)=> setCheckings(e.target.value)}
                    required/>
                <Button
                    variant="contained"
                    color="primary"
                    type="submit"
                    sx={{mt:2}}
                >
                    Submit
                </Button>

                </form>
        </Box>
    )
}

export default IncomeBaselineForm;