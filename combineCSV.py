import csv

CSVFiles = ["add_array_mem.csv", "add_array_time.csv", "add_list_mem.csv", "add_list_time.csv",
            "gen_array_mem.csv", "gen_array_time.csv", "gen_list_mem.csv", "gen_list_time.csv",
            "mul_array_mem.csv", "mul_array_time.csv", "mul_list_mem.csv", "mul_list_time.csv",
            "pro_array_mem.csv", "pro_array_time.csv", "pro_list_mem.csv", "pro_list_time.csv"]

combinedCsv = [["Term Amount", 
                "Add Array Memory", "Add Array Time", "Add List Memory", "Add List Time",
                "Generate Array Memory", "Generate Array Time", "Generate List Memory", "Generate List Time",
                "Multiply Array Memory", "Multiply Array Time", "Multiply List Memory", "Multiply List Time",
                "Process Array Memory", "Process Array Time", "Process List Memory", "Process List Time"],
                ["Term Amount", 
                "Array", "Array", "List", "List",
                "Array", "Array", "List", "List",
                "Array", "Array", "List", "List",
                "Array", "Array", "List", "List"]]

combinedCsvData = []

for i in range(0, 500):
    for j in range(0, 5):
        combinedCsvData.append([i*10, 
                                0, 0, 0, 0,
                                0, 0, 0, 0,
                                0, 0, 0, 0,
                                0, 0, 0, 0])


for i in range(0, len(CSVFiles)):
    csvFile = open(CSVFiles[i], "r")
    reader = csv.reader(csvFile)
    k = 0
    first = True
    for val in reader:
        if first:
            first = False
            continue
        if i % 2 == 1:
            combinedCsvData[k][i+1] = val[1]
            k += 1
        else:
            for p in range(0, 5):
                combinedCsvData[k][i+1] = val[1]
                k += 1

csvFile = open("combined.csv", "x", newline="")
writer = csv.writer(csvFile)
for row in combinedCsv:
    writer.writerow(row)
for row in combinedCsvData:
    writer.writerow(row)