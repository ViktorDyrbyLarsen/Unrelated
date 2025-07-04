import os
import json

# Path to your export folder
export_folder = r'C:/Users/Bruger/Documents/Chat-Logs/'

# Path to your conversations.json file
conversations_json_path = os.path.join(export_folder, 'conversations.json')

# Output folder for filtered conversations
filtered_folder = os.path.join(export_folder, 'filtered_FAGPROJEKT')
os.makedirs(filtered_folder, exist_ok=True)

# Load the conversations
with open(conversations_json_path, 'r', encoding='utf-8') as f:
    conversations = json.load(f)

kept = 0

# Filter conversations
for idx, conversation in enumerate(conversations):
    title = conversation.get('title', '')
    if '[FAGPROJEKT]' in title:
        output_file = os.path.join(filtered_folder, f'conversation_{idx+1}.json')
        with open(output_file, 'w', encoding='utf-8') as out_f:
            json.dump(conversation, out_f, ensure_ascii=False, indent=2)
        kept += 1

print(f"Filtered {kept} conversations into '{filtered_folder}' folder.")
