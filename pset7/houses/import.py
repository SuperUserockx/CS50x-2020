from sys import argv, exit
import csv
import cs50


def main():
    if len(argv) != 2:
        print("Usage: python impot.py data.csv")
        exit(1)
    dict_database = loadDatabase(argv[1])
    # print (dict_database)

    STR = []
#     STRCount = []
    for key in dict_database[0].keys():
        STR.append(key)
    # print (STR)
    open(f"students.db", "w").close()   # Making sure that the database is empty
    db = cs50.SQL("sqlite:///students.db")
    # Creating the database
    db.execute("CREATE TABLE students (id INT, first TEXT, middle TEXT, last TEXT, house TEXT, birth NUMERIC, PRIMARY KEY(id))")
    for i in range(len(dict_database)):
        name = str(dict_database[i].get('name'))
        name = name.split(" ")
        if len(name) != 2:
            db.execute("INSERT INTO students (id, first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?, ?)", i,
                       name[0], name[1], name[2], dict_database[i].get('house'), dict_database[i].get('birth'))  # Loading Data into the database
            # name[1] = name[len(name)-1]
        else:
            db.execute("INSERT INTO students (id, first, last, house, birth) VALUES(?, ?, ?, ?, ?)", i,
                       name[0], name[1], dict_database[i].get('house'), dict_database[i].get('birth'))  # Loading Data into the database
        # print(name[0])


def loadDatabase(file):
    reader = csv.DictReader(open(file, 'r'))
    dict_list = []
    for line in reader:
        dict_list.append(line)
    return dict_list


main()
