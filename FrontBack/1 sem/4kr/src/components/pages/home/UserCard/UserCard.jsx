import './UserCard.css';

function UserCard({ name, role, avatarUrl}) {
    return (
        <div className="user-card">
            <div className="avatar-section">
                <img src={avatarUrl} alt={`Аватар ${name}`} />
            </div>
            <div className="user-info">
                <h3>{name}</h3>
                <p>{role}</p>
            </div>
        </div>
    );
}
export default UserCard;