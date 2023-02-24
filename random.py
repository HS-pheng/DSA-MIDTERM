import csv
import random
from faker import Faker

fake = Faker()

# Define the fields for the CSV file
fields = ['id', 'title', 'author', 'genre', 'publishDate']

# Generate 500 rows of dummy data
data = []
for i in range(500):
    row = {
        'id': i + 1,
        'title': fake.sentence(nb_words=5),
        'author': fake.name(),
        'genre': random.choice(['Fiction', 'Non-fiction']),
        'publishDate': fake.date_this_century()
    }
    data.append(row)

# Save the data to a CSV file
with open('library_data.csv', 'w', newline='') as csvfile:
    writer = csv.DictWriter(csvfile, fieldnames=fields)
    writer.writeheader()
    for row in data:
        writer.writerow(row)
