from sys import argv, exit
import csv


def main():
    # if len(argv) != 3:
    #     print("Usage: python dna.py data.csv sequence.txt")
    #     exit(1)
    dict_database = loadDatabase(argv[1])
    with open(argv[2], "r") as seq:
        data = seq.readlines()
    data = str(data)
    # print (data)
    STR = []
    STRCount = []
    for key in dict_database[0].keys():
        STR.append(key)
    STR.pop(0)
    # print(STRCount)
    for i in range(len(STR)):
        # ST = STR[i]
        STRCount.append(maxRepete(STR[i], data))

    # print (dict_database)
    # print (STRCount)
    # STRout = []
    # STRout.
    # print (dict_database[0].get('name'))
    # print(f"Found {dict_database['fred']}")
    # print(f"Found {STR[STRCount]}")
    for i in range(len(dict_database)):
        found = 1
        for j in range(len(STR)):
            t1 = int(dict_database[i].get(STR[j]))
            t2 = STRCount[j]
            if t1 != t2:
                found = 0
                break
        if found == 1:
            print(dict_database[i].get('name'))
            found = 2
            break
    if found != 2:
        print("No match")
        

def maxRepete(STR, data):
    maxCount = 0
    curCount = 0
    Ldata = len(data)
    Lstr = len(STR)
    i = 0
    while i < Ldata:
        temp = i+Lstr
        dt = data[i:temp]
        if (i < Ldata - Lstr and STR == dt):
            curCount += 1
            i += Lstr
        else:
            if curCount > maxCount:
                maxCount = curCount
            curCount = 0
            i += 1
    return maxCount


def loadDatabase(file):
    # f = open(file,'r')
    # reader = csv.reader(f)
    # data_dict = {}
    # for row in reader:
    #     data_dict[row[0]] = {row[1],row[2]}
    # return data_dict
    reader = csv.DictReader(open(file, 'r'))
    dict_list = []
    for line in reader:
        dict_list.append(line)
    return dict_list


main()
