import { useState, useEffect, useRef } from 'react';
import './SearchPage.css';

function SearchPage() {
    const [searchTerm, setSearchTerm] = useState('');
    const [searchResults, setSearchResults] = useState([]);
    const [loading, setLoading] = useState(false);
    const [allTasks, setAllTasks] = useState([]);
    const [selectedStatuses, setSelectedStatuses] = useState([]);
    const searchTimeoutRef = useRef(null);
    const abortControllerRef = useRef(null);

    const loadTasks = () => {
        const saved = localStorage.getItem('tasks');
        if (saved) {
            setAllTasks(JSON.parse(saved));
        }
    };

    useEffect(() => {
        loadTasks();

        window.addEventListener('focus', loadTasks);

        return () => {
            window.removeEventListener('focus', loadTasks);
        };
    }, []);

    const searchTasks = async (query) => {
        if (abortControllerRef.current) {
            abortControllerRef.current.abort();
        }

        abortControllerRef.current = new AbortController();

        try {
            setLoading(true);

            loadTasks();

            if (!query.trim()) {
                setSearchResults([]);
                setLoading(false);
                return;
            }

            await new Promise((resolve, reject) => {
                const timeout = setTimeout(resolve, 300);
                abortControllerRef.current.signal.addEventListener('abort', () => {
                    clearTimeout(timeout);
                    reject(new Error('Aborted'));
                });
            });

            const lowerQuery = query.toLowerCase();
            const filtered = allTasks.filter(task =>
                task.title.toLowerCase().includes(lowerQuery) ||
                task.orderId.toString().toLowerCase().includes(lowerQuery)
            );

            setSearchResults(filtered);
        } catch (err) {
            if (err.message !== 'Aborted') {
                console.error('Ошибка поиска:', err);
            }
        } finally {
            setLoading(false);
        }
    };

    const handleSearchChange = (e) => {
        const value = e.target.value;
        setSearchTerm(value);

        if (searchTimeoutRef.current) {
            clearTimeout(searchTimeoutRef.current);
        }

        searchTimeoutRef.current = setTimeout(() => {
            searchTasks(value);
        }, 500);
    };

    useEffect(() => {
        return () => {
            if (searchTimeoutRef.current) {
                clearTimeout(searchTimeoutRef.current);
            }
            if (abortControllerRef.current) {
                abortControllerRef.current.abort();
            }
        };
    }, []);

    const handleClear = () => {
        setSearchTerm('');
        setSearchResults([]);
    };

    const handleStatusToggle = (status) => {
        setSelectedStatuses(prev =>
            prev.includes(status)
                ? prev.filter(s => s !== status)
                : [...prev, status]
        );
    };

    const filteredResults = searchResults.filter(task => {
        if (selectedStatuses.length === 0) {
            return true;
        }
        return selectedStatuses.includes(task.status);
    });

    return (
        <div className="page search-page">
            <div className="page-header">
                <h1>Поиск технологий</h1>
            </div>

            <div className="search-container">
                <div className="search-box-wrapper">
                    <input
                        type="text"
                        placeholder="Введите название задачи или заказ..."
                        value={searchTerm}
                        onChange={handleSearchChange}
                        className="search-input-large"
                    />
                    {loading && (
                        <div className="search-loader">
                            <div className="spinner-mini"></div>
                        </div>
                    )}
                    {searchTerm && (
                        <button onClick={handleClear} className="clear-button">
                            ✕
                        </button>
                    )}
                </div>

                <div className="filter-container">
                    <button
                        className={`filter-button ${selectedStatuses.includes('not-started') ? 'active' : ''}`}
                        onClick={() => handleStatusToggle('not-started')}
                    >
                        Не начато
                    </button>
                    <button
                        className={`filter-button ${selectedStatuses.includes('in-progress') ? 'active' : ''}`}
                        onClick={() => handleStatusToggle('in-progress')}
                    >
                        В процессе
                    </button>
                    <button
                        className={`filter-button ${selectedStatuses.includes('completed') ? 'active' : ''}`}
                        onClick={() => handleStatusToggle('completed')}
                    >
                        Завершено
                    </button>
                </div>

                <div className="search-info">
                    {searchTerm ? (
                        loading ? (
                            <p>Поиск...</p>
                        ) : (
                            <p>Найдено результатов: <strong>{filteredResults.length}</strong></p>
                        )
                    ) : (
                        <p>Начните вводить для поиска среди {allTasks.length} задач</p>
                    )}
                </div>
            </div>

            <div className="search-results-section">
                {filteredResults.length > 0 ? (
                    <div className="results-grid">
                        {filteredResults.map(tech => (
                            <div key={tech.id} className="result-card">
                                <div className="result-header">
                                    <h3>{tech.title}</h3>
                                    <span className={`status-indicator status-${tech.status}`}>
                                        {tech.status === 'completed' && '✅'}
                                        {tech.status === 'in-progress' && '🔄'}
                                        {tech.status === 'not-started' && '⏸️'}
                                    </span>
                                </div>
                                <p className="result-description">{tech.notes}</p>
                                <div className="result-footer">
                                    <span className="result-category">
                                        📁 Заказ №{tech.orderId}
                                    </span>
                                </div>
                            </div>
                        ))}
                    </div>
                ) : (
                    searchTerm && !loading && (
                        <div className="no-results">
                            <div className="no-results-icon">🔍</div>
                            <h3>Ничего не найдено</h3>
                            <p>Попробуйте изменить поисковый запрос</p>
                        </div>
                    )
                )}
            </div>
        </div>
    );
}
export default SearchPage;