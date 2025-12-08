import './ProgressBar.css';

function ProgressBar({
     progress,
     label = '',
     height = 30,
     showPercentage = true,
     animated = false
 }) {
    const normalizedProgress = Math.min(100, Math.max(0, progress));

    const outerStyle = {
        height: `${height}px`,
    };

    const innerStyle = {
        width: `${normalizedProgress}%`,
        backgroundPositionX: animated ? `-${normalizedProgress}%` : '0%'
    };

    return (
        <div className="progress-bar-container">
            <div className="progress-bar-outer" style={outerStyle}>
                {(label || showPercentage) && (
                    <div className="progress-bar-header">
                        {label && <span className="progress-bar-label">{label}</span>}
                        {showPercentage && (
                            <span className="progress-bar-percentage">{normalizedProgress}%</span>
                        )}
                    </div>
                )}
                <div
                    className={`progress-bar-inner ${animated ? 'animated' : ''}`}
                    style={innerStyle}
                />
            </div>
        </div>
    );
}
export default ProgressBar;