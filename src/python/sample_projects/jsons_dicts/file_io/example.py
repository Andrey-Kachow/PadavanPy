import json

my_file = open('some_data.csv', 'r')

headers = None
columns = []
for line in my_file.readlines():
    if headers is None:
        headers = line.strip().split(",")
    else:
        columns.append(line.strip().split(","))
my_file.close()

json_list = []
for column in columns:
    json_obj = {}
    for i in range(len(headers)):
        json_obj[headers[i]] = column[i]
    json_list.append(json_obj)

json_string = json.dumps(json_list)

with open('some_data.json', 'w') as my_json_file:
    my_json_file.write(json_string)