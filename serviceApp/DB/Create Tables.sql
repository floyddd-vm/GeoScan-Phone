CREATE TABLE contacts(
	ID INTEGER PRIMARY KEY AUTOINCREMENT,
	FirstName TEXT,
	SecondName TEXT,
	PhoneNumber TEXT
);

CREATE TABLE status(
	ID INTEGER PRIMARY KEY,
	Status TEXT
);

CREATE TABLE logs(
	LogID INTEGER PRIMARY KEY, 
	ContactID INTEGER
	Date TEXT,
	Time TEXT,
	StatusID INTEGER,
	FOREIGN KEY(ContactID) 
		REFERENCES contacts(ID),
	FOREIGN KEY(StatusID) 
		REFERENCES Status(ID)
);



CREATE TABLE messages(
	MsgID INTEGER PRIMARY KEY,
	SenderID INTEGER,
	RecipientID INTEGER,
	Date TEXT,
	Time TEXT,
	Text TEXT,
	FOREIGN KEY(SenderID) 
		REFERENCES contacts(ID),
	FOREIGN KEY(RecipientID) 
		REFERENCES contacts(ID)
);