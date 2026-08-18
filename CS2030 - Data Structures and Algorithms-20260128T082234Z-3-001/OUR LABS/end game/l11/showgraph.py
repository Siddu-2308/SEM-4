import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import os

FILE_PATH = 'graph.txt'
REFRESH_CHECK = 1000  # Check for file changes every 1 second
last_modified_time = 0

fig, ax = plt.subplots(figsize=(8, 6))
G = nx.Graph()

def update(frame):
    global last_modified_time
    
    if not os.path.exists(FILE_PATH):
        return

    # Check if the file has actually been modified
    current_mtime = os.path.getmtime(FILE_PATH)
    if current_mtime <= last_modified_time:
        return  # Skip redrawing if file hasn't changed

    last_modified_time = current_mtime
    #print(f"File change detected! Redrawing...")

    G.clear()
    ax.clear()
    
    try:
        with open(FILE_PATH, 'r') as f:
            for line in f:
                if ':' in line:
                    node, neighbors = line.split(':')
                    node = node.strip()
                    G.add_node(node);
                    for neighbor in neighbors.split(','):
                        neighbor = neighbor.strip()
                        if neighbor:
                            G.add_edge(node, neighbor)
        
        pos = nx.circular_layout(G)
        # pos = nx.spring_layout(G)
        nx.draw(G, pos, ax=ax, with_labels=True, node_color='orange', 
                node_size=500, edge_color='black', font_weight='bold')
        ax.set_title(f"Live Graph (Last Updated: {os.path.basename(FILE_PATH)})")
        
    except Exception as e:
        print(f"Error reading file: {e}")

# Check every 1000ms, but 'update' only redraws if mtime changed
ani = FuncAnimation(fig, update, interval=REFRESH_CHECK, cache_frame_data=False)

plt.show()
