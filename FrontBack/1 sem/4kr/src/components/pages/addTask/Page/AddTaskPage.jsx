import { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import Modal from '../../../pkg/Modal/Modal';
import useTasks from '../../../../hooks/tasks';
import './AddTaskPage.css';

function AddTaskPage() {
    const { addTask, addTasks } = useTasks();
    const navigate = useNavigate();
    const [formData, setFormData] = useState({
        title: '',
        orderId: '',
        status: 'not-started',
        notes: ''
    });
    const [isLoading, setIsLoading] = useState(false);
    const [isImportModalOpen, setIsImportModalOpen] = useState(false);
    const [jsonInput, setJsonInput] = useState('');

    const handleInputChange = (e) => {
        const { name, value } = e.target;
        setFormData(prev => ({
            ...prev,
            [name]: value
        }));
    };

    const handleSubmit = (e) => {
        e.preventDefault();
        if (formData.title.trim() && formData.orderId) {
            addTask({
                title: formData.title,
                orderId: parseInt(formData.orderId),
                status: formData.status,
                notes: formData.notes
            });
            alert('Задание успешно добавлено!');
            setFormData({
                title: '',
                orderId: '',
                status: 'not-started',
                notes: ''
            });
        } else {
            alert('Заполните название и номер заказа!');
        }
    };

    const handleImportFromJSON = () => {
        try {
            const parsedData = JSON.parse(jsonInput);
            
            if (Array.isArray(parsedData)) {
                // Проверяем, что каждый элемент имеет необходимые поля
                const validTasks = parsedData.filter(task => 
                    task.title && task.orderId
                ).map(task => ({
                    title: task.title,
                    orderId: parseInt(task.orderId),
                    status: task.status || 'not-started',
                    notes: task.notes || ''
                }));
                
                if (validTasks.length > 0) {
                    addTasks(validTasks);
                    alert(`Успешно импортировано ${validTasks.length} заданий!`);
                    setJsonInput('');
                    setIsImportModalOpen(false);
                    navigate('/');
                } else {
                    alert('Не найдено валидных заданий в JSON. Убедитесь, что каждое задание имеет поля title и orderId.');
                }
            } else {
                alert('JSON должен содержать массив заданий!');
            }
        } catch (error) {
            console.error('Ошибка парсинга JSON:', error);
            alert('Неверный формат JSON. Проверьте правильность данных.');
        }
    };

    const handleImportFromAPI = async () => {
        setIsLoading(true);
        try {
            const response = await fetch('https://dummyjson.com/products');
            const data = await response.json();
            
            if (data.products && data.products.length > 0) {
                const newTasks = data.products.map(product => {
                    const hash = product.id + Math.floor(product.price * 100);
                    const statusIndex = Math.floor(Math.abs(hash) % 3);
                    const statuses = ['not-started', 'in-progress', 'completed'];
                    
                    const orderId = Math.floor((Math.abs(hash) % 10) + 1);
                    
                    return {
                        title: product.title,
                        orderId: orderId,
                        status: statuses[statusIndex],
                        notes: product.description || ''
                    };
                });
                
                addTasks(newTasks);
                alert(`Успешно импортировано ${newTasks.length} заданий!`);
                navigate('/');
            }
        } catch (error) {
            console.error('Ошибка при загрузке данных:', error);
            alert('Не удалось загрузить данные из API');
        } finally {
            setIsLoading(false);
        }
    };

    return (
        <div className="page add-task-page">
            <div className="add-task-container">
                <h1 className="page-title">➕ Добавить задание</h1>
                
                <div className="import-section">
                    <button 
                        onClick={() => setIsImportModalOpen(true)} 
                        className="import-button json-import"
                    >
                        📋 Импортировать из JSON
                    </button>
                    <p className="import-hint">
                        Вставьте JSON данные с заданиями
                    </p>
                    
                    <button 
                        onClick={handleImportFromAPI} 
                        className="import-button api-import"
                        disabled={isLoading}
                    >
                        {isLoading ? '⏳ Загрузка...' : '🌐 Распарсить задания из API'}
                    </button>
                    <p className="import-hint">
                        Загрузить задания с dummyjson.com/products
                    </p>
                </div>

                <div className="form-container">
                    <h2 className="form-title">Создать новое задание вручную</h2>
                    <form onSubmit={handleSubmit} className="task-form">
                        <div className="form-group">
                            <label htmlFor="title">Название задания *</label>
                            <input
                                type="text"
                                id="title"
                                name="title"
                                value={formData.title}
                                onChange={handleInputChange}
                                placeholder="Введите название..."
                                required
                            />
                        </div>

                        <div className="form-group">
                            <label htmlFor="orderId">Номер заказа *</label>
                            <input
                                type="number"
                                id="orderId"
                                name="orderId"
                                value={formData.orderId}
                                onChange={handleInputChange}
                                placeholder="Введите номер заказа..."
                                min="1"
                                required
                            />
                        </div>

                        <div className="form-group">
                            <label>Статус</label>
                            <div className="status-buttons">
                                <button
                                    type="button"
                                    className={`status-button not-started ${formData.status === 'not-started' ? 'active' : ''}`}
                                    onClick={() => setFormData(prev => ({ ...prev, status: 'not-started' }))}
                                >
                                    ⭕ Не начато
                                </button>
                                <button
                                    type="button"
                                    className={`status-button in-progress ${formData.status === 'in-progress' ? 'active' : ''}`}
                                    onClick={() => setFormData(prev => ({ ...prev, status: 'in-progress' }))}
                                >
                                    🔄 В процессе
                                </button>
                                <button
                                    type="button"
                                    className={`status-button completed ${formData.status === 'completed' ? 'active' : ''}`}
                                    onClick={() => setFormData(prev => ({ ...prev, status: 'completed' }))}
                                >
                                    ✅ Завершено
                                </button>
                            </div>
                        </div>

                        <div className="form-group">
                            <label htmlFor="notes">Заметки</label>
                            <textarea
                                id="notes"
                                name="notes"
                                value={formData.notes}
                                onChange={handleInputChange}
                                placeholder="Введите заметки..."
                                rows="4"
                            />
                        </div>

                        <div className="form-actions">
                            <button type="submit" className="submit-button">
                                ✅ Добавить задание
                            </button>
                            <button 
                                type="button" 
                                className="cancel-button"
                                onClick={() => navigate('/')}
                            >
                                ❌ Отмена
                            </button>
                        </div>
                    </form>
                </div>

                <Modal
                    isOpen={isImportModalOpen}
                    onClose={() => setIsImportModalOpen(false)}
                    title="Импорт заданий из JSON"
                >
                    <div className="import-modal-content">
                        <p className="import-instruction">
                            Вставьте JSON массив заданий. Каждое задание должно содержать поля: title, orderId, status (опционально), notes (опционально).
                        </p>
                        <textarea
                            className="import-textarea"
                            value={jsonInput}
                            onChange={(e) => setJsonInput(e.target.value)}
                            placeholder='[{"title": "Название", "orderId": 1, "status": "not-started", "notes": "Заметки"}]'
                        />
                        <div className="import-buttons">
                            <button onClick={handleImportFromJSON} className="import-confirm-button">
                                ✅ Импортировать
                            </button>
                            <button onClick={() => setIsImportModalOpen(false)} className="import-cancel-button">
                                ❌ Отмена
                            </button>
                        </div>
                    </div>
                </Modal>
            </div>
        </div>
    );
}

export default AddTaskPage;
