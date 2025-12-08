import { NavLink, useLocation } from 'react-router-dom';
import { useState, useEffect } from 'react';
import './Navigation.css';

function Navigation() {
    const [isExpanded, setIsExpanded] = useState(false);
    const [lastScrollY, setLastScrollY] = useState(0);
    const location = useLocation();

    useEffect(() => {
        const handleScroll = () => {
            const currentScrollY = window.scrollY;
            
            // Сворачиваем при прокрутке вниз (только на мобильных)
            if (window.innerWidth <= 768 && currentScrollY > lastScrollY && currentScrollY > 50) {
                setIsExpanded(false);
            }
            
            setLastScrollY(currentScrollY);
        };

        window.addEventListener('scroll', handleScroll, { passive: true });
        return () => window.removeEventListener('scroll', handleScroll);
    }, [lastScrollY]);

    // Закрываем меню при смене маршрута
    useEffect(() => {
        setIsExpanded(false);
    }, [location]);

    const toggleExpanded = () => {
        setIsExpanded(!isExpanded);
    };

    return (
        <nav className={`navigation ${isExpanded ? 'expanded' : ''}`}>
            <div className="nav-container">
                <div className="nav-brand">
                    <span className="nav-logo">📋</span>
                    <span className="nav-title">Управление задачами</span>
                </div>
                <ul className="nav-links">
                    <li>
                        <NavLink 
                            to="/" 
                            className={({ isActive }) => isActive ? 'nav-link active' : 'nav-link'}
                            onClick={isExpanded ? toggleExpanded : undefined}
                        >
                            🏠 Главная
                        </NavLink>
                    </li>
                    <li>
                        <NavLink 
                            to="/statistics" 
                            className={({ isActive }) => isActive ? 'nav-link active' : 'nav-link'}
                            onClick={isExpanded ? toggleExpanded : undefined}
                        >
                            📊 Статистика
                        </NavLink>
                    </li>
                    <li>
                        <NavLink 
                            to="/search" 
                            className={({ isActive }) => isActive ? 'nav-link active' : 'nav-link'}
                            onClick={isExpanded ? toggleExpanded : undefined}
                        >
                            🔍 Поиск
                        </NavLink>
                    </li>
                    <li>
                        <NavLink 
                            to="/add-task" 
                            className={({ isActive }) => isActive ? 'nav-link active' : 'nav-link'}
                            onClick={isExpanded ? toggleExpanded : undefined}
                        >
                            ➕ Добавить
                        </NavLink>
                    </li>
                </ul>
                <button className="nav-toggle" onClick={toggleExpanded} aria-label="Toggle navigation">
                    {isExpanded ? '✕' : '☰'}
                </button>
            </div>
        </nav>
    );
}

export default Navigation;
