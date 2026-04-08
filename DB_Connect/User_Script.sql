CREATE TABLE Member (
    member_id INT PRIMARY KEY
);

CREATE TABLE RunningRecord (
    record_id INT AUTO_INCREMENT PRIMARY KEY,
    member_id INT NOT NULL,
    run_time DOUBLE NOT NULL,
    avg_speed DECIMAL(3,1) NOT NULL,
    distance DECIMAL(6,3) NOT NULL,
    calorie DECIMAL(5,1) NOT NULL,
    record_date DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (member_id) REFERENCES Member(member_id)
);

INSERT INTO Member (member_id) VALUES (1);