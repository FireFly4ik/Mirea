import { useState } from 'react';

const initTasks = [
    { id: 1, title: 'БигМак', orderId: 1, status: 'completed', notes: '' },
    { id: 2, title: 'Картошка фри', orderId: 1, status: 'in-progress', notes: '' },
    { id: 3, title: 'Кола', orderId: 1, status: 'not-started', notes: '' },
    { id: 4, title: 'Чизбургер', orderId: 2, status: 'not-started', notes: '' },
    { id: 5, title: 'Наггетсы', orderId: 2, status: 'completed', notes: '' },
    { id: 6, title: 'Молочный коктейль', orderId: 2, status: 'in-progress', notes: '' },
    { id: 7, title: 'Филе-О-Фиш', orderId: 3, status: 'not-started', notes: '' },
    { id: 8, title: 'Картошка по-деревенски', orderId: 3, status: 'not-started', notes: '' },
    { id: 9, title: 'Апельсиновый сок', orderId: 3, status: 'completed', notes: '' },
];

function useStorage(key, initialValue) {
    const [storedValue, setStoredValue] = useState(() => {
        try {
            const item = window.localStorage.getItem(key);
            return item ? JSON.parse(item) : initialValue;
        } catch (error) {
            console.error(`Ошибка чтения из localStorage ключа "${key}"`, error);
            return initialValue;
        }
    });

    const setValue = (value) => {
        try {
            const valueToStore = value instanceof Function ? value(storedValue) : value;
            setStoredValue(valueToStore)
            window.localStorage.setItem(key, JSON.stringify(valueToStore));
        } catch (error) {
            console.error(`Ошибка записи в localStorage ключа "${key}":`, error);
        }
    };

    return [storedValue, setValue];
}

function useTasks() {
    const [tasks, setTasks] = useStorage('tasks', initTasks);

    const updateStatus = (id) => {
        setTasks(prev => prev.map(task => {
            if (task.id === id) {
                let newStatus;
                if (task.status === 'not-started') {
                    newStatus = 'in-progress'
                } else if (task.status === 'in-progress') {
                    newStatus = 'completed'
                } else {
                    newStatus = 'not-started'
                }
                return {...task, status: newStatus}
            }
            return task;
        }))
    }

    const updateNotes = (taskId, newNotes) => {
        setTasks(prev => prev.map(task =>
                task.id === taskId ? {...task, notes: newNotes } : task
            )
        );
    };

    const markAllCompleted = () => {
        setTasks(prev => prev.map(task => ({ ...task, status: 'completed' })));
    };

    const resetAllStatuses = () => {
        setTasks(prev => prev.map(task => ({ ...task, status: 'not-started' })));
    };

    const addTask = (newTask) => {
        setTasks(prev => {
            const maxId = prev.length > 0 ? Math.max(...prev.map(t => t.id)) : 0;
            return [...prev, { ...newTask, id: maxId + 1 }];
        });
    };

    const addTasks = (newTasks) => {
        setTasks(prev => {
            const maxId = prev.length > 0 ? Math.max(...prev.map(t => t.id)) : 0;
            const tasksWithIds = newTasks.map((task, index) => ({
                ...task,
                id: maxId + index + 1
            }));
            return [...prev, ...tasksWithIds];
        });
    };

    const updateTask = (taskId, updatedData) => {
        setTasks(prev => prev.map(task =>
            task.id === taskId ? { ...task, ...updatedData } : task
        ));
    };

    return {
        tasks,
        updateStatus,
        updateNotes,
        markAllCompleted,
        resetAllStatuses,
        addTask,
        addTasks,
        updateTask
    }
}
export default useTasks;