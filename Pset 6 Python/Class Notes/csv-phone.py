from sys import exit
import csv

file = open("phonebook.csv", "a")

name = input("Name: ")

try:
    number = int(input("Number: "))
except:
    print("This is not a number! ")
    exit(1)

writer = csv.writer(file)
writer.writerow([name, number])
file.close()

print("Clang!")

