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
#%%
from sympy import *
init_printing()
#%%
b,c = symbols('b c')
x1, y1, z1 = symbols('x1 y1 z1')
x2, y2, z2 = symbols('x2 y2 z2')
def L(x,y,z):
    return (2*x  - 4*y + 3*z + b,6*x + c*x*y*z)

# %%
display(L(x1 + x2, y1 + y2, z1 + z2)[1].expand())
display(L(x1, y1, z1)[1] + L(x2, y2, z2)[1])

# %%
display(((x1 + x2)*(y1 + y2)).expand() - (x1*y1 + x2*y2))