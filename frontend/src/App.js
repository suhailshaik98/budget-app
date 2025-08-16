import logo from './logo.svg';
import './App.css';
import IncomeBaselineForm from './components/IncomeBaselineForm';
import SetupLayout  from './components/UserAccountSetup/UserAccountSetup';
import AccountSetupForm from "./components/UserAccountSetup/Step1/Step1";
import AccountSetupForm2 from "./components/UserAccountSetup/Step2/Step2";
import Step3 from './components/UserAccountSetup/Summary';
import HomePageLayout from './components/Dashboard/Dashboard';
import { BrowserRouter as Router, Routes, Route, Navigate } from "react-router-dom";

function App() {
  return (
    <Router> {/* <-- must be at the root */}
      <Routes>
        <Route path="/" element={<HomePageLayout />} /> {/* Added HomePageLayout route */}
        {/* <Route path="/" element={<Home />} /> */}

        <Route path="setup" element={<SetupLayout />}>
          <Route index element={<Navigate to="step1" />} />
          <Route path="step1" element={<AccountSetupForm />} />
          <Route path="step2" element={<AccountSetupForm2 />} />
          <Route path="step3" element={<Step3 />} />
        </Route>
      </Routes>
    </Router>
  );
}
export default App;
