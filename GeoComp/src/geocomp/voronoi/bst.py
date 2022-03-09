from geocomp.common.guiprim import dist2

class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

def insert(root, data, key):
    if isinstance(data, tuple):
        root = Node(data)
        root.left = insert(root.left, data[0], key)
        root.right = insert(root.right, data[1], key)
        return root

    if root is None:
        return Node(data)

    if root.left is None:
        root.left = Node((root.data, None))
        root.right = Node((data, root.data))
        root.right.left = Node((data, ))
        root.right.right = Node((root.data, ))
        root.data = (root.data, data)
        return root

    if dist2(key(data), key(root.data[0])) < dist2(key(data), key(root.data[1])):
        root.left = insert(root.left, data, key)
    else:
        root.right = insert(root.right, data, key)

    return root

def search(root, data, key):
    if not isinstance(data, tuple):
        return root.data

    if dist2(key(data), key(root.data[0])) < dist2(key(data), key(root.data[1])):
        root.left = search(root.left, data, key)
    else:
        root.right = search(root.right, data, key)

def circle_event(root, data, key):
    left = right = root

    while left.left is not None:
        left = left.left

    while right.right is not None:
        right = right.right

    if data != left.data and data != right.data:
        return True

    return False

# def delete(root, key, func=lambda x: x):
#     if root is None:
#         return None, None

#     if float_left(func(root.data[0][1]), func(root.data[0][0]), func(key)):
#         root.left, data = delete(root.left, key, func)
#         return root, data

#     if not float_left_on(func(root.data[2][1]), func(root.data[2][0]), func(key)):
#         root.right, data = delete(root.right, key, func)
#         return root, data

#     data = root.data

#     if root.left is None and root.right is None:
#         return None, data

#     if root.left is None:
#         return root.right, data

#     if root.right is None:
#         return root.left, data

#     succParent = root
#     succ = root.right

#     while succ.left is not None:
#         succParent = succ
#         succ = succ.left

#     if succParent != root:
#         succParent.left = succ.right
#     else:
#         succParent.right = succ.right

#     root.key = succ.key
#     root.data = succ.data

#     return root, data

def printTree(node, i=0):
    if node is None:
        if i == 0:
            print("Empty tree")
        return

    printTree(node.left, i+3)
    print(i*" ", node.data)
    printTree(node.right, i+3)
