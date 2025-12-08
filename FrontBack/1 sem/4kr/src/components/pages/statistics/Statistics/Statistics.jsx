import './Statistics.css';
import {useEffect, useState} from "react";
import ProgressBar from "../ProgressBar/ProgressBar";

function Statistics() {
    const [tasks, setTasks] = useState([]);
    const [stats, setStats] = useState({
        total: 0,
        completed: 0,
        inProgress: 0,
        notStarted: 0,
        progress: 0,
        inProgressPercentage: 0,
        notStartedPercentage: 0
    });
    const [ordersInProgress, setOrdersInProgress] = useState([]);

    useEffect(() => {
        const loadTasks = () => {
            const saved = localStorage.getItem('tasks');
            if (saved) {
                const tasksData = JSON.parse(saved);
                setTasks(tasksData);

                const completed = tasksData.filter(t => t.status === 'completed').length;
                const inProgress = tasksData.filter(t => t.status === 'in-progress').length;
                const notStarted = tasksData.filter(t => t.status === 'not-started').length;
                const total = tasksData.length;

                setStats({
                    total,
                    completed,
                    inProgress,
                    notStarted,
                    progress: total > 0 ? Math.round((completed / total) * 100) : 0,
                    inProgressPercentage: total > 0 ? Math.round((inProgress / total) * 100) : 0,
                    notStartedPercentage: total > 0 ? Math.round((notStarted / total) * 100) : 0
                });

                const orders = Object.values(
                    tasksData.reduce((acc, task) => {
                        acc[task.orderId] = acc[task.orderId] || { orderId: task.orderId, tasks: [] };
                        acc[task.orderId].tasks.push(task);
                        return acc;
                    }, {})
                ).map(order => {
                    const totalTasks = order.tasks.length;
                    const completedTasks = order.tasks.filter(t => t.status === 'completed').length;
                    const progress = totalTasks > 0 ? Math.round((completedTasks / totalTasks) * 100) : 0;
                    return { ...order, progress };
                }).filter(order => order.progress > 0 && order.progress < 100);

                setOrdersInProgress(orders);
            }
        };

        loadTasks();
        window.addEventListener('focus', loadTasks);
        return () => window.removeEventListener('focus', loadTasks);
    }, tasks);

    console.log(ordersInProgress);

    return (
        <div className="statistics">
            <div className="page-header">
                <h1>Статистика задач</h1>
            </div>

            <div className="stats-container">
                <div className="stat-card">
                    <div className="stat-icon">📚</div>
                    <div className="stat-content"><div className="stat-value">{stats.total}</div><div className="stat-label">Всего задач</div></div>
                </div>
                <div className="stat-card">
                    <div className="stat-icon">✅</div>
                    <div className="stat-content"><div className="stat-value">{stats.completed}</div><div className="stat-label">Завершено</div></div>
                </div>
                <div className="stat-card">
                    <div className="stat-icon">🔄</div>
                    <div className="stat-content"><div className="stat-value">{stats.inProgress}</div><div className="stat-label">В процессе</div></div>
                </div>
                <div className="stat-card">
                    <div className="stat-icon">⏸️</div>
                    <div className="stat-content"><div className="stat-value">{stats.notStarted}</div><div className="stat-label">Не начато</div></div>
                </div>
            </div>
            <div className="progress-chart">
                <h2>Общий прогресс по статусам</h2>
                <div className="progress-rings-container">
                    <ul className="progress-rings">
                        <li className="progress">
                            <svg viewBox="0 0 200 200" className="progress-ring">
                                <defs><linearGradient id="gradient-completed"><stop offset="0%" stopColor="#4CAF50"/><stop offset="100%" stopColor="#8BC34A"/></linearGradient></defs>
                                <circle className="progress-ring-bg" cx="100" cy="100" r="85"/>
                                <circle className="progress-ring-fill" cx="100" cy="100" r="85" style={{strokeDasharray: `${stats.progress * 5.34} 534`, stroke: 'url(#gradient-completed)'}}/>
                            </svg>
                            <div className="progress-text"><div className="progress-percentage">{stats.progress}%</div><div className="progress-subtitle">Завершено</div></div>
                        </li>
                        <li className="progress">
                            <svg viewBox="0 0 200 200" className="progress-ring">
                                <defs><linearGradient id="gradient-in-progress"><stop offset="0%" stopColor="#FFC107"/><stop offset="100%" stopColor="#FFEB3B"/></linearGradient></defs>
                                <circle className="progress-ring-bg" cx="100" cy="100" r="85"/>
                                <circle className="progress-ring-fill" cx="100" cy="100" r="85" style={{strokeDasharray: `${stats.inProgressPercentage * 5.34} 534`, stroke: 'url(#gradient-in-progress)'}}/>
                            </svg>
                            <div className="progress-text"><div className="progress-percentage">{stats.inProgressPercentage}%</div><div className="progress-subtitle">В процессе</div></div>
                        </li>
                        <li className="progress">
                            <svg viewBox="0 0 200 200" className="progress-ring">
                                <defs><linearGradient id="gradient-not-started"><stop offset="0%" stopColor="#F44336"/><stop offset="100%" stopColor="#E57373"/></linearGradient></defs>
                                <circle className="progress-ring-bg" cx="100" cy="100" r="85"/>
                                <circle className="progress-ring-fill" cx="100" cy="100" r="85" style={{strokeDasharray: `${stats.notStartedPercentage * 5.34} 534`, stroke: 'url(#gradient-not-started)'}}/>
                            </svg>
                            <div className="progress-text"><div className="progress-percentage">{stats.notStartedPercentage}%</div><div className="progress-subtitle">Не начато</div></div>
                        </li>
                    </ul>
                </div>
                <div className="orders-progress-section">
                    <h2>Статистика заказов в процессе</h2>
                    <div className="orders-progress-grid">
                        {ordersInProgress.length > 0 ? (
                            ordersInProgress.map(order => (
                                <div key={order.orderId} className="order-progress-item">
                                    <ProgressBar
                                        progress={order.progress}
                                        label={`Заказ №${order.orderId}`}
                                        animated={true}
                                    />
                                </div>
                            ))
                        ) : (
                            <p className="no-orders-message">Нет заказов в процессе.</p>
                        )}
                    </div>
                </div>
            </div>
        </div>
    );
}
export default Statistics;