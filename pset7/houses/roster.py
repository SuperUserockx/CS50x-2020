# TODO
from sys import argv, exit
import cs50


def main():
    if len(argv) != 2:
        print("Usage: python impot.py houseName")
        exit(1)
    house = str(argv[1])
    # print (house)
    db = cs50.SQL("sqlite:///students.db")
    data = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", house)
    # print(data)
    for i in range(len(data)):
        if data[i].get('middle') is None:
            print(f"{data[i].get('first')} {data[i].get('last')}, born {data[i].get('birth')}")
        else:
            print(f"{data[i].get('first')} {data[i].get('middle')} {data[i].get('last')}, born {data[i].get('birth')}")
  
      
main()