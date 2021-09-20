create_db_path:
	mkdir -p data/db
	mkdir -p data/logs

run_db: create_db_path
	rm data/logs/mongo.log --force
	sudo mongod --port 27017 --dbpath data/db --logpath data/logs/mongo.log &

check_db_running:
	sudo lsof -i -P | grep mongod

connect_mongo:
	mongo --port 27017

import_jsons:
	mongoimport tv-shows.json -d movieData -c movies --jsonArray --drop
	mongoimport boxoffice.json -d boxOffice -c movieStarts --jsonArray --drop
	mongoimport boxoffice-extended.json -d boxOffice -c exmoviestarts --jsonArray --drop
	mongoimport persons.json -d contactData -c contacts --jsonArray --drop
	mongoimport array-data.json -d contactData -c friends --jsonArray --drop