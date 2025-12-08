import './TaskNotes.css'

function TaskNotes({ notes, onNotesChange, taskId }) {
    return (
        <div className="notes-section">
            <h4>Заметки:</h4>
            <textarea
                value={notes}
                onChange={(e) => onNotesChange(taskId, e.target.value)}
                placeholder="Записывайте сюда важные моменты блюда..."
                rows="3"
            />
            <div className="notes-hint">
                {notes.length > 0 ? `Заметка сохранена (${notes.length} символов)` :
                    'Добавьте заметку'}
            </div>
        </div>
    );
}

export default TaskNotes;