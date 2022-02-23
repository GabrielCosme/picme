from geocomp.common.guiprim import *

class Node:
    def __init__(self, key, data=None):
        self.key = key
        self.data = data
        self.left = None
        self.right = None

def insert(root, key, data=None, func=lambda x: x):
    if root is None:
        return Node(key, data)

    if float_left(func(root.data[2][1]), func(root.data[2][0]), func(key)):
        root.left = insert(root.left, key, data, func)
    else:
        root.right = insert(root.right, key, data, func)

    return root

def delete(root, key, func=lambda x: x):
    if root is None:
        return None, None

    if float_left(func(root.data[0][1]), func(root.data[0][0]), func(key)):
        root.left, data = delete(root.left, key, func)
        return root, data

    if not float_left_on(func(root.data[2][1]), func(root.data[2][0]), func(key)):
        root.right, data = delete(root.right, key, func)
        return root, data

    data = root.data

    if root.left is None and root.right is None:
        return None, data

    if root.left is None:
        return root.right, data

    if root.right is None:
        return root.left, data

    succParent = root
    succ = root.right

    while succ.left is not None:
        succParent = succ
        succ = succ.left

    if succParent != root:
        succParent.left = succ.right
    else:
        succParent.right = succ.right

    root.key = succ.key
    root.data = succ.data

    return root, data

def printTree(node, i=0):
    if node is None:
        if i == 0:
            print("Empty tree")
        return

    printTree(node.left, i+3)
    print(i*" ", node.key)
    printTree(node.right, i+3)
