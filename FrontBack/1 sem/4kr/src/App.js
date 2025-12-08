import './App.css';
import { BrowserRouter, Routes, Route } from 'react-router-dom';
import Navigation from './components/pkg/Navigation/Navigation';
import HomePage from './components/pages/home/Page/HomePage';
import StatisticsPage from "./components/pages/statistics/Page/StatisticsPage";
import SearchPage from "./components/pages/search/Page/SearchPage";
import AddTaskPage from "./components/pages/addTask/Page/AddTaskPage";

function App() {
    return (
        <BrowserRouter>
            <div className="App">
                <Navigation />
                <Routes>
                    <Route path="/" element={<HomePage />} />
                    <Route path="/statistics" element={<StatisticsPage />} />
                    <Route path="/search" element={<SearchPage />} />
                    <Route path="/add-task" element={<AddTaskPage />} />
                </Routes>
            </div>
        </BrowserRouter>
    );
}
export default App;