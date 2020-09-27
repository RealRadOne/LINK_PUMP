import json
jsonFile = open("result.json","r")
data = json.loads(jsonFile.read())
jsonFile.close()
print ( 'Parsing through ', data['name'], ' chat history...')

def createRow(date, user, tags, link):
    row = [date, user]
    # Append tags
    for tag in tags:
        row.append(tag)
    row.append(link)
    return row
    
def getTags(tagsText):
    tagsText = tagsText.replace('\n','')
    tagsText.strip()
    tagList = tagsText.split(',')
    while( len(tagList) < 3 ):
        tagList.append('')
    return tagList[:3]

outCSV = open("out.csv","w")
outCSV.write('Date,User,Tag1,Tag2,Tag3,Link\n')
for message in data['messages']:
    
    if(message['type']!='message'):
        continue
    tags = ['','','']
    foundLink = False

    """
    Message['text'] is of form:
        [   'normal text', 
            {   'type' : 'link/bot_command',
                'text' : '<url>'
        }]
    """
    for t in message['text']:
        # Check if normal text
        if( isinstance(t,str) ):
            tags = getTags(t)
            continue
        # Check if text of type link
        if( t['type'] == 'link'):
            link = t['text']
            foundLink = True
    
    if(not foundLink):
        continue;
    
    date = message['date']
    user = message['from']    
    row = createRow(date, user, tags, link)
    delimiter = ","
    outCSV.write(delimiter.join(row)+'\n')
