import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import os
import time

FILE_PATH = 'graph.txt'
REFRESH_CHECK = 1000
last_modified_time = 0

fig, ax = plt.subplots(figsize=(8, 6))
G = nx.DiGraph()
pos = {}
force_redraw = False  # 👈 new flag

def update(frame):
    global last_modified_time, pos, force_redraw

    if not os.path.exists(FILE_PATH):
        return

    current_mtime = os.path.getmtime(FILE_PATH)

    # Only update if file changed OR forced by click
    if current_mtime <= last_modified_time and not force_redraw:
        return

    last_modified_time = current_mtime
    force_redraw = False  # reset flag

    new_G = nx.DiGraph()

    try:
        with open(FILE_PATH, 'r') as f:
            for line in f:
                if ':' not in line:
                    continue

                node, neighbors = line.split(':', 1)
                node = node.strip()
                if(not new_G.has_node(node)):
                    new_G.add_node(node)
                for neighbor in neighbors.split(','):
                    neighbor = neighbor.strip()
                    if not neighbor:
                        continue

                    # Handle thick edges (_ prefix)
                    if neighbor.startswith('_'):
                        neighbor_name = neighbor[1:]
                        new_G.add_edge(node, neighbor_name, weight=3)
                    else:
                        new_G.add_edge(node, neighbor, weight=1)

        # 👇 If forced redraw → reset layout
        if not pos or force_redraw:
            pos = nx.spring_layout(new_G)  # new random layout
        else:
            pos = nx.spring_layout(new_G, pos=pos, fixed=pos.keys())

        G.clear()
        G.add_nodes_from(new_G.nodes(data=True))
        G.add_edges_from(new_G.edges(data=True))
        stedgelist = []
        curvedgelist = []
        stedgewidths = []
        curvedgewidths = []
        for u, v, data in G.edges(data=True):
            if G.has_edge(v,u):
                curvedgelist.append((u,v))
                curvedgewidths.append(data['weight'])
            else:
                stedgelist.append((u,v))
                stedgewidths.append(data['weight'])

        ax.clear()

        # Node colors
        node_colors = []
        for n in G.nodes():
            node_colors.append('orange')

        # Edge widths
        edge_widths = [G[u][v].get('weight', 1) for u, v in G.edges()]

        nx.draw_networkx_nodes(G, pos, node_color=node_colors, node_size=500);
        nx.draw_networkx_labels(G, pos, font_size=12, font_family='sans-serif')
        nx.draw_networkx_edges(
            G, pos, ax=ax,
            edgelist=curvedgelist,
            edge_color='black',
            width=curvedgewidths,   
            arrows=True,
            connectionstyle="arc3,rad=0.2",
            node_size=500
        )
        nx.draw_networkx_edges(
            G, pos, ax=ax,
            edgelist=stedgelist,
            edge_color='black',
            width=stedgewidths,
            arrows=True,
            node_size=500
        )
        ax.set_title(f"Live Graph (Updated: {time.strftime('%H:%M:%S')})")

    except Exception as e:
        print(f"Error reading file: {e}")

# 👇 Mouse click handler
def on_click(event):
    global force_redraw, pos
    force_redraw = True
    pos = {}  # reset layout so it randomizes
    #print("Manual redraw triggered")

# Connect click event
fig.canvas.mpl_connect('button_press_event', on_click)

ani = FuncAnimation(
    fig,
    update,
    interval=REFRESH_CHECK,
    cache_frame_data=False
)

plt.tight_layout()
plt.show()