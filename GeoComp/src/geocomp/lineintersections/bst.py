from geocomp.common.guiprim import *

class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None

def createTree(pre, key, mini=float("-infinity"), maxi=float("infinity")):
    if createTree.preIndex >= len(pre):
        return None

    root = None

    if mini < key < maxi:
        root = Node(key)
        createTree.preIndex += 1

        if createTree.preIndex < len(pre):
            root.left = createTree(pre, pre[createTree.preIndex], mini, key)

        if createTree.preIndex < len(pre):
            root.right = createTree(pre, pre[createTree.preIndex], key, maxi)

    return root

createTree.preIndex = 0

def insert(root, key, func=lambda x: x):
    if root is None:
        return Node(key)

    area = area2(func(root.key).init, func(root.key).to, func(key).init)

    if area > 0 or (area == 0 and area2(func(root.key).init, func(root.key).to, func(key).to) > 0):
        root.left = insert(root.left, key, func)
    else:
        root.right = insert(root.right, key, func)

    return root

def delete(root, key, func=lambda x: x):
    if root is None:
        return None

    area_to = area2(func(root.key).init, func(root.key).to, func(key).to)
    area_init = area2(func(root.key).init, func(root.key).to, func(key).init)

    if area_to > 0 or (area_to == 0 and area_init < 0):
        root.left = delete(root.left, key, func)
        return root

    if area_to < 0 or (area_to == 0 and area_init > 0):
        root.right = delete(root.right, key, func)
        return root

    if root.left is None and root.right is None:
        return None

    if root.left is None:
        return root.right

    if root.right is None:
        return root.left

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

    return root

def search(root, key):
    if root is None or root.key == key:
        return root

    if root.key < key:
        return search(root.right, key)

    return search(root.left, key)

def predecessor(root, key, func):
    if root is None:
        tmp = predecessor.aux
        predecessor.aux = None
        return tmp

    if area2(func(root.key).init, func(root.key).to, key) == 0:
        if root.left is not None:
            tmp = root.left
            while tmp.right:
                tmp = tmp.right
            predecessor.aux = tmp

        tmp = predecessor.aux
        predecessor.aux = None
        return tmp

    if area2(func(root.key).init, func(root.key).to, key) > 0:
        return predecessor(root.left, key, func)

    predecessor.aux = root
    return predecessor(root.right, key, func)

predecessor.aux = None

def successor(root, key, func):
    if root is None:
        tmp = successor.aux
        successor.aux = None
        return tmp

    if area2(func(root.key).init, func(root.key).to, key) == 0:
        if root.right is not None:
            tmp = root.right
            while tmp.left:
                tmp = tmp.left
            successor.aux = tmp

        tmp = successor.aux
        successor.aux = None
        return tmp

    if area2(func(root.key).init, func(root.key).to, key) > 0:
        successor.aux = root
        return successor(root.left, key, func)

    return successor(root.right, key, func)

successor.aux = None

def printTree(node, i=0):
    if node is None:
        return

    printTree(node.left, i+3)
    print(i*" ", node.key)
    printTree(node.right, i+3)
