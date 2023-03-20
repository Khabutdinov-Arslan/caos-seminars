import psycopg2
from time import sleep

conn = psycopg2.connect(host="localhost", user="postgres", password="postgres", dbname="postgres")
cursor = conn.cursor()
cursor.execute("SELECT * FROM users")
res = cursor.fetchall()
print(res)
sleep(30)
conn.close()
