from telethon import TelegramClient, sync
import pandas as pd
import json 

api_id = 2899
api_hash = '36722c72256a24c1225de00eb6a1ca74'
client = TelegramClient('session_name', api_id, api_hash).start()
group_username = 'LDumpTest'
client.start()

participants = client.get_participants(group_username)

username = []
if len(participants):
    for x in participants:
        username.append(x.username)

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
    while( len(tagList) < 4 ):
        tagList.append('')
    return tagList[:4]

outCSV = open("out.csv","w")
outCSV.write('Date,User,Tag1,Tag2,Tag3,Link\n')    

chats =client.get_messages(group_username, 10)
# n number of messages to be extracted
# Get message id, message, sender id, reply to message id, and timestamp

if len(chats):
    for chat in chats:
        cur=str(chat.message)
        data = ['','','','']
        foundLink = False
        data=getTags(cur)
        tags=data[:3]
        link=data[3]
        sender= chat.get_sender().username
        print(sender)
        row = createRow(str(chat.date),str(sender), tags, link)
        delimiter = ','
        outCSV.write(delimiter.join(row)+'\n')



