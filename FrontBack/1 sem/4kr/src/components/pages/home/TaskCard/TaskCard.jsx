import './TaskCard.css';
import TaskNotes from "../TaskNotes/TaskNotes";
import React from 'react';

const TaskCard = React.forwardRef(({task, onStatusChange, onNotesChange, onClick}, ref) => {
    const localStatus = task.status === 'completed' ? 'Завершён' : task.status === 'in-progress' ? 'В процессе' : 'Ждёт начала';

    const handleCardClick = (e) => {
        // Не открываем модальное окно при клике на элементы с собственными обработчиками
        if (e.target.closest('.status') || e.target.closest('.task-notes')) {
            return;
        }
        if (onClick) {
            onClick();
        }
    };

    return (
        <div className="task-card"
             data-status={task.status}
             ref={ref}
             onClick={handleCardClick}
             style={{cursor: 'pointer'}}
        >
            <h3>{task.title}</h3>
            <p>Заказ №{task.orderId}</p>
            <p
                className="status"
                onClick={onStatusChange}
            >
                Статус: {localStatus}
            </p>
            <TaskNotes notes={task.notes} onNotesChange={onNotesChange} taskId={task.id} />
        </div>
    );
});
export default TaskCard;