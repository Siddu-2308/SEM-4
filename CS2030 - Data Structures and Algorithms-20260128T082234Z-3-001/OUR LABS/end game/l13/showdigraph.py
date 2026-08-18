import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from matplotlib.widgets import Button
import os
import time
import math

FILE_PATH = 'graph.txt'
REFRESH_CHECK = 1000
last_modified_time = 0

fig, ax = plt.subplots(figsize=(8, 6))
plt.subplots_adjust(top=0.9)  # space for button
plt.autoscale(enable=False)

G = nx.DiGraph()
pos = {}
force_redraw = False

dragging_node = None  # currently dragged node

# ---------- GRAPH UPDATE ----------
def update(frame):
    global last_modified_time, pos, force_redraw

    if not os.path.exists(FILE_PATH):
        return

    current_mtime = os.path.getmtime(FILE_PATH)

    if current_mtime <= last_modified_time and not force_redraw:
        return

    last_modified_time = current_mtime

    new_G = nx.DiGraph()

    try:
        with open(FILE_PATH, 'r') as f:
            for line in f:
                if ':' not in line:
                    continue

                node, neighbors = line.split(':', 1)
                node = node.strip()

                if not new_G.has_node(node):
                    new_G.add_node(node)

                for neighbor in neighbors.split(','):
                    neighbor = neighbor.strip()
                    if not neighbor:
                        continue

                    if neighbor.startswith('_'):
                        new_G.add_edge(node, neighbor[1:], weight=3, color = "black")
                    elif neighbor.startswith('+'):
                        new_G.add_edge(node, neighbor[1:], weight=3, color = "red")
                    elif neighbor.startswith('*'):
                        new_G.add_edge(node, neighbor[1:], weight=3, color = "blue")
                    else:
                        new_G.add_edge(node, neighbor, weight=1, color = "black")

        # Layout handling
        if not pos or force_redraw:
            pos = nx.spring_layout(new_G)
        else:
            common_nodes = set(pos.keys()) & set(new_G.nodes())
            pos = nx.spring_layout(
                new_G,
                pos={k: pos[k] for k in common_nodes},
                fixed=common_nodes
            )

        force_redraw = False

        G.clear()
        G.add_nodes_from(new_G.nodes(data=True))
        G.add_edges_from(new_G.edges(data=True))

        draw_graph()

    except Exception as e:
        print(f"Error reading file: {e}")

# ---------- DRAW ----------
def draw_graph():
    ax.clear()
    ax.set_axis_off()

    stedgelist = []
    curvedgelist = []
    stedgewidths = []
    curvedgewidths = []
    stedgecolors = []
    curvedgecolors = []

    for u, v, data in G.edges(data=True):
        if G.has_edge(v, u):
            curvedgelist.append((u, v))
            curvedgewidths.append(data['weight'])
            curvedgecolors.append(data['color'])
        else:
            stedgelist.append((u, v))
            stedgewidths.append(data['weight'])
            stedgecolors.append(data['color'])

    nx.draw_networkx_nodes(G, pos, node_color='orange', node_size=500, ax=ax)
    nx.draw_networkx_labels(G, pos, font_size=12, ax=ax)

    nx.draw_networkx_edges(
        G, pos, edgelist=curvedgelist,
        connectionstyle="arc3,rad=0.2",
        width=curvedgewidths,
        edge_color=curvedgecolors,
        arrows=True,
        arrowstyle='-|>',
        node_size=500,
        ax=ax
    )

    nx.draw_networkx_edges(
        G, pos, edgelist=stedgelist,
        width=stedgewidths,
        edge_color=stedgecolors,
        arrows=True,
        arrowstyle='-|>',
        node_size=500,
        ax=ax
    )
#    ax.set_title(f"Live Graph (Updated: {time.strftime('%H:%M:%S')})")
    fig.canvas.draw_idle()

# ---------- NODE DRAGGING ----------
def get_node_at_position(event):
    """Return closest node within threshold"""
    if event.xdata is None or event.ydata is None:
        return None

    threshold = 0.05  # adjust sensitivity

    for node, (x, y) in pos.items():
        dist = math.hypot(x - event.xdata, y - event.ydata)
        if dist < threshold:
            return node
    return None

def on_press(event):
    global dragging_node
    dragging_node = get_node_at_position(event)

def on_release(event):
    global dragging_node
    dragging_node = None

def on_motion(event):
    global dragging_node

    if dragging_node is None:
        return

    if event.xdata is None or event.ydata is None:
        return

    pos[dragging_node] = (event.xdata, event.ydata)
    draw_graph()

# ---------- BUTTON ----------
def on_button_clicked(event):
    global force_redraw, pos
    force_redraw = True
    pos = {}  # reset layout

# Add button
button_ax = plt.axes([0.4, 0.93, 0.2, 0.05])
button = Button(button_ax, 'Redraw Layout')
button.on_clicked(on_button_clicked)

# Connect mouse events
fig.canvas.mpl_connect('button_press_event', on_press)
fig.canvas.mpl_connect('button_release_event', on_release)
fig.canvas.mpl_connect('motion_notify_event', on_motion)

# Animation loop
ani = FuncAnimation(
    fig,
    update,
    interval=REFRESH_CHECK,
    cache_frame_data=False
)

plt.show()