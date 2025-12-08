import './ProgressHeader.css'

function ProgressHeader({amount, studied}) {
    let progress = Math.round(studied / amount * 100)

    return (
        <div className="progress-header">
            <div className="progress-header-label">
                <p>Всего задач: {amount}</p>
                <p>Выполнено: {studied}</p>
            </div>

            <div className="progress-bar-container">
                <div
                    className="progress-bar-fill"
                    style={{width: `${progress}%`}}
                ></div>
            </div>
            <span className="progress-bar-text">{progress}%</span>
        </div>
    );
}

export default ProgressHeader;