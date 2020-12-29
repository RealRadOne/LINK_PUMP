from telethon import TelegramClient
import pandas as pd

api_id = 2899
api_hash = '36722c72256a24c1225de00eb6a1ca74'
group_username = 'link_dump'
NUM_MESSAGES = 10*10*100  # last 10 links per 10 users over 100 days 


client = TelegramClient('session_name', api_id, api_hash)

async with client:
    chats = await client.get_messages(group_username, NUM_MESSAGES)

previous_links_df = pd.read_csv("data_dummy.csv", error_bad_lines=False, parse_dates=['Date'])

last_datetime = max(previous_links_df.Date)

def getTags(message):
    tagList = message.replace('\n','').strip().split(',')
    link = tagList[-1]
    tags = tagList[:-1] 
    tags += ['']*(3 - len(tags))
    return tags, link


# Get message id, message, sender id, reply to message id, and timestamp
new_links = []

for chat in chats:
    date = chat.date
    if date <= last_datetime:
        break

    tags, link = getTags(chat.message)
    sender = chat.get_sender().username
    new_links.append([str(date), str(sender)] + tags + [link])
    

new_links_df = pd.DataFrame(new_links, columns=previous_links_df.columns)

new_links_df.append(previous_links_df) \
            .to_csv('data_dummy.csv', index=False)
