class Node:
    def __init__(self, data, parent=None):
        self.data = data
        self.left = None
        self.right = None
        self.parent = parent

def PriorityQueue(list, key):
    root = None
    for data in list:
        root = insert(root, data, key)

    return root

def insert(root, data, key, parent=None):
    if root is None:
        return Node(data, parent)

    if key(data) > key(root.data):
        root.left, root.right = root.right, root.left
        root.right = insert(root.right, root.data, key, parent=root)
        root.data = data
    elif root.right is not None and key(data) > key(root.right.data):
        root.right = insert(root.right, data, key, parent=root)
    else:
        root.left = insert(root.left, data, key, parent=root)

    return root

def delete(root, key):
    if root is None:
        return None

    if root.right is None and root.left is None:
        return None

    if root.right is None:
        root.left.parent = root.parent
        return root.left

    if root.left is None:
        root.right.parent = root.parent
        return root.right

    root.data = root.right.data
    root.right = delete(root.right, key)

    return root

def printTree(node, i=0):
    if node is None:
        if i == 0:
            print("Empty tree")
        return

    printTree(node.left, i+3)
    print(i*" ", node.data)
    printTree(node.right, i+3)
