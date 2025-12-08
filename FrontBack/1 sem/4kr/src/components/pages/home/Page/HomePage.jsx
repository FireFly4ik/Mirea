import {useState, useRef, createRef} from "react";
import TaskCard from "../TaskCard/TaskCard";
import UserCard from "../UserCard/UserCard";
import ProgressHeader from "../ProgressHeader/ProgressHeader";
import Modal from "../../../pkg/Modal/Modal";
import EditTaskModal from "../EditTaskModal/EditTaskModal";
import useTasks from "../../../../hooks/tasks";
import './HomePage.css';

function HomePage() {
    const {tasks, updateStatus, updateNotes, markAllCompleted, resetAllStatuses, updateTask} = useTasks();
    const [nextTask, setNextTask] = useState(null);
    const [isExportModalOpen, setIsExportModalOpen] = useState(false);
    const [isEditModalOpen, setIsEditModalOpen] = useState(false);
    const [editingTask, setEditingTask] = useState(null);
    const taskRefs = useRef({});
    taskRefs.current = tasks.reduce((acc, task) => {
        acc[task.id] = acc[task.id] ?? createRef();
        return acc;
    }, taskRefs.current || {});

    const completed = tasks.filter(task => task.status === 'completed').length;

    const handleSelectRandom = () => {
        const availableTasks = tasks.filter(order => order.status !== 'completed');
        if (availableTasks.length > 0) {
            const randomIndex = Math.floor(Math.random() * availableTasks.length);
            setNextTask(availableTasks[randomIndex]);
        } else {
            setNextTask({ title: 'Все задачи выполнены!', orderId: '' });
        }
    };

    const handleScrollToTask = () => {
        if (nextTask && taskRefs.current[nextTask.id]) {
            taskRefs.current[nextTask.id].current.scrollIntoView({
                behavior: 'smooth',
                block: 'center'
            });
        }
    };

    const handleCopyJSON = () => {
        const jsonData = JSON.stringify(tasks, null, 2);
        navigator.clipboard.writeText(jsonData).then(() => {
            alert('Данные скопированы в буфер обмена!');
        }).catch(err => {
            console.error('Ошибка копирования:', err);
            alert('Не удалось скопировать данные');
        });
    };

    const handleDownloadJSON = () => {
        const jsonData = JSON.stringify(tasks, null, 2);
        const blob = new Blob([jsonData], { type: 'application/json' });
        const url = URL.createObjectURL(blob);
        const link = document.createElement('a');
        link.href = url;
        link.download = `tasks_export_${new Date().toISOString().split('T')[0]}.json`;
        document.body.appendChild(link);
        link.click();
        document.body.removeChild(link);
        URL.revokeObjectURL(url);
    };

    const handleTaskClick = (task) => {
        setEditingTask(task);
        setIsEditModalOpen(true);
    };

    const handleSaveTask = (updatedData) => {
        if (editingTask) {
            updateTask(editingTask.id, updatedData);
        }
    };

    return (
        <div className="page home-page">
            <UserCard
                name="Айнурочка"
                role="Администратор"
                avatarUrl="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcRfVMhpKmVy_-iwfRLAiNiaDslMa-2oEz7KTw&s"
            />

            <ProgressHeader
                amount={tasks.length}
                studied={completed}
            />

            <div className="task-controls">
                <button onClick={markAllCompleted} className="control-button">
                    ✅ Отметить все как выполненные
                </button>
                <button onClick={resetAllStatuses} className="control-button">
                    🔄 Сбросить все статусы
                </button>
                <button onClick={handleSelectRandom} className="control-button">
                    🎲 Случайный выбор следующего задания
                </button>
                <button onClick={() => setIsExportModalOpen(true)} className="control-button">
                    📥 Экспорт данных
                </button>

                {nextTask && (
                    <div className="next-task-display" onClick={handleScrollToTask} style={{cursor: 'pointer'}}>
                        Следующее задание: <strong>{nextTask.title}</strong>
                        {nextTask.orderId && ` (Заказ №${nextTask.orderId})`}
                    </div>
                )}
            </div>

            <ul>
                {tasks.map(task =>
                    <li key={task.id}>
                        <TaskCard
                            ref={taskRefs.current[task.id]}
                            task={task}
                            onStatusChange={() => updateStatus(task.id)}
                            onNotesChange={updateNotes}
                            onClick={() => handleTaskClick(task)}
                        />
                    </li>
                )}
            </ul>

            <Modal
                isOpen={isExportModalOpen}
                onClose={() => setIsExportModalOpen(false)}
                title="Экспорт данных"
            >
                <div className="export-modal-content">
                    <textarea
                        className="export-textarea"
                        value={JSON.stringify(tasks, null, 2)}
                        readOnly
                    />
                    <div className="export-buttons">
                        <button onClick={handleCopyJSON} className="export-button copy">
                            📋 Скопировать
                        </button>
                        <button onClick={handleDownloadJSON} className="export-button download">
                            💾 Скачать JSON
                        </button>
                    </div>
                </div>
            </Modal>

            <EditTaskModal
                isOpen={isEditModalOpen}
                onClose={() => setIsEditModalOpen(false)}
                task={editingTask}
                onSave={handleSaveTask}
            />
        </div>
    );
}
export default HomePage;