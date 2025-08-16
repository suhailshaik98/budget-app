import { Outlet, useLocation, useNavigate } from "react-router-dom";
import {
  TextField,
  Button,
  Box,
  Typography,
  IconButton,
  Divider
} from '@mui/material';
import ButtonAppBar from "../TopBar/ButtonAppBar";
function SetupLayout() {
  const navigate = useNavigate();
  const location = useLocation();
  console.log(window.location.hostname); // e.g., "example.com" or "192.168.1.10"
  var apiUrl = window.location.hostname; // Default to localhost for developmen
  const steps = ["/setup/step1", "/setup/step2","/setup/step3"];
  const currentIndex = steps.indexOf(location.pathname);

  const goNext = () => {
    if (currentIndex < steps.length - 1) {
      navigate(steps[currentIndex + 1]);
    }
  };

  const goBack = () => {
    if (currentIndex > 0) {
      navigate(steps[currentIndex - 1]);
    }
  };

  return (
    <div>
            <ButtonAppBar />
            <Box
      sx={{
        maxWidth: 800,
        mx: "auto",    // margin-left/right auto
        p: 2           // padding
      }}
    >
      <Outlet />


    </Box>
    <Box
  sx={{
    mt: 2,
    display: 'flex',
    justifyContent: 'space-between',
    px: 1.5,
    maxWidth: 400,  // limits how wide the buttons can spread
    mx: 'auto'      // centers the box horizontally on the page
  }}
>
  <Button onClick={goBack} disabled={currentIndex === 0}>
    Back
  </Button>
  <Button
    variant="contained"
    onClick={goNext}
    disabled={currentIndex === steps.length - 1}
  >
    Next
  </Button>
</Box>
    </div>

  );
}

export default SetupLayout;
