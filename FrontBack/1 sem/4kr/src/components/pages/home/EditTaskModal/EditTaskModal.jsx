import { useState, useEffect } from 'react';
import Modal from '../../../pkg/Modal/Modal';
import './EditTaskModal.css';

function EditTaskModal({ isOpen, onClose, task, onSave }) {
    const [formData, setFormData] = useState({
        title: '',
        orderId: '',
        status: 'not-started',
        notes: ''
    });

    useEffect(() => {
        if (task) {
            setFormData({
                title: task.title || '',
                orderId: task.orderId || '',
                status: task.status || 'not-started',
                notes: task.notes || ''
            });
        }
    }, [task]);

    const handleInputChange = (e) => {
        const { name, value } = e.target;
        setFormData(prev => ({
            ...prev,
            [name]: value
        }));
    };

    const handleStatusChange = (newStatus) => {
        setFormData(prev => ({
            ...prev,
            status: newStatus
        }));
    };

    const handleSubmit = (e) => {
        e.preventDefault();
        if (formData.title.trim() && formData.orderId) {
            onSave({
                ...formData,
                orderId: parseInt(formData.orderId)
            });
            onClose();
        } else {
            alert('Заполните название и номер заказа!');
        }
    };

    if (!task) return null;

    return (
        <Modal isOpen={isOpen} onClose={onClose} title="Редактировать задание">
            <form onSubmit={handleSubmit} className="edit-task-form">
                <div className="form-group">
                    <label htmlFor="edit-title">Название задания *</label>
                    <input
                        type="text"
                        id="edit-title"
                        name="title"
                        value={formData.title}
                        onChange={handleInputChange}
                        placeholder="Введите название..."
                        required
                    />
                </div>

                <div className="form-group">
                    <label htmlFor="edit-orderId">Номер заказа *</label>
                    <input
                        type="number"
                        id="edit-orderId"
                        name="orderId"
                        value={formData.orderId}
                        onChange={handleInputChange}
                        placeholder="Введите номер заказа..."
                        min="1"
                        required
                    />
                </div>

                <div className="form-group">
                    <label>Статус *</label>
                    <div className="status-buttons">
                        <button
                            type="button"
                            className={`status-button not-started ${formData.status === 'not-started' ? 'active' : ''}`}
                            onClick={() => handleStatusChange('not-started')}
                        >
                            ⭕ Не начато
                        </button>
                        <button
                            type="button"
                            className={`status-button in-progress ${formData.status === 'in-progress' ? 'active' : ''}`}
                            onClick={() => handleStatusChange('in-progress')}
                        >
                            🔄 В процессе
                        </button>
                        <button
                            type="button"
                            className={`status-button completed ${formData.status === 'completed' ? 'active' : ''}`}
                            onClick={() => handleStatusChange('completed')}
                        >
                            ✅ Завершено
                        </button>
                    </div>
                </div>

                <div className="form-group">
                    <label htmlFor="edit-notes">Заметки</label>
                    <textarea
                        id="edit-notes"
                        name="notes"
                        value={formData.notes}
                        onChange={handleInputChange}
                        placeholder="Введите заметки..."
                        rows="4"
                    />
                </div>

                <div className="edit-form-actions">
                    <button type="submit" className="save-button">
                        💾 Сохранить
                    </button>
                    <button type="button" className="cancel-edit-button" onClick={onClose}>
                        ❌ Отмена
                    </button>
                </div>
            </form>
        </Modal>
    );
}

export default EditTaskModal;
