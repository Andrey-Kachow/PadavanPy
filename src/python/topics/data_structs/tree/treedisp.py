from tree import *
import random, os, webbrowser


class TreeDisplay:

    NUM_COLORS = 6
    TARGET_DIR = "templates"

    def __init__(self, tree):
        self.tree = tree

    def create_html(self):
        return ""

    def create_html_file(self, filename):
        with open(filename, "w") as f:
            f.write(self.create_html())

    def display(self, filename=None):
        if filename is None:
            filename = os.path.join(os.path.abspath(TreeDisplay.TARGET_DIR), "trd_test.html")
        self.create_html_file(filename)
        webbrowser.open('file://' + os.path.realpath(filename))


class TreeDisplayHTML(TreeDisplay):

    def create_html(self):
        return """
            <!doctype html>
            <html>
            <head>
              <title>Tree</title>
              <style>
              .col_trunk { background: #000000; }
              .col_1 { background: #AD7BF6; }
              .col_2 { background: #F7E6D5; }
              .col_3 { background: #FF97A3; }
              .col_4 { background: #CC99FF; }
              .col_5 { background: #FECCCC; }
              .col_6 { background: #FC6C85; }
              .tree {
                min-width: 10px;
                display: flex;
                border: solid 1px #ff2244;
              }
              .node { min-width: 30px; }
              .connector { width: 4px; }
              .blacker {
                position: relative;
                -ms-transform: translateY(-50%);
                transform: translateY(-50%);
                width: 100%;
                top: 50%;
              }
              .tostr {
                color: #ffffff;
              }
            </style>
            </head>
            <body>
            """ + f"{self.tree_html(self.tree, 1)}" + """
            </body>
            </html>
        """

    def tree_html(self, tree, depth):
        if tree is None:
            return ""
        return f"""
            <div class="tree col_{depth % TreeDisplayHTML.NUM_COLORS}">
                <div class="node">
                    <div class="blacker col_trunk">
                        <span class="tostr col_trunk">
                            { tree.value }
                        </span>
                    </div>
                </div>

                <div class="branches">
                    { self.tree_html(tree.right, depth + random.randint(1, 3)) }
                    { self.tree_html(tree.left, depth + random.randint(1, 3)) }
                </div>
            </div>
        """


def memcopy_array(sub, arr, x, y):
    try:
        for i in range(len(sub)):
            for j in range(len(sub[0])):
                arr[y + i][x + j] = sub[i][j]
    except Exception as e:
        print(sub)
        print(arr)
        print(y, x, i, j)
        raise e


class ArrayBlocks:

    @staticmethod
    def leaf(value):
        return [
            ["+"],
            [value],
            [" "]
        ]

    @staticmethod
    def unary_con(node_value, child):
        width = len(child[0])
        two_more_rows = [[" " for x in range(width)] for y in range(2)]
        count = 0
        while child[0][count] == " ":
            count += 1
        two_more_rows[0][count] = "+"
        two_more_rows[1][count] = node_value
        return two_more_rows + child

    @staticmethod
    def binary_con(node_value, left, right):
        width = len(left[0]) + len(right[0])
        if width % 2 == 0:
            width += 1
        height = max(len(left), len(right))
        new_array = [[" " for x in range(width)] for y in range(height)]
        memcopy_array(left, new_array, 0, 0)
        memcopy_array(right, new_array, width - len(right[0]), 0)
        two_more_rows = [[b for x in range(width)] for b in [" ", "+"]]
        middle = width // 2
        two_more_rows[0][middle] = "+"
        two_more_rows[1][middle] = node_value
        count = 0
        while new_array[0][count] == " ":
            two_more_rows[1][count] = " "
            count += 1
        count = len(new_array[0]) - 1
        while new_array[0][count] == " ":
            two_more_rows[1][count] = " "
            count -= 1
        return two_more_rows + new_array


class TreeDisplayArrayHTML(TreeDisplay):

    def __init__(self, tree):
        super().__init__(tree)
        self.array = self.get_array_from_tree(tree)

    def get_array_from_tree(self, tree):
        if tree.is_leaf():
            return ArrayBlocks.leaf(tree.value)
        if tree.left is None:
            return ArrayBlocks.unary_con(
                tree.value,
                self.get_array_from_tree(tree.right)
            )
        if tree.right is None:
            return ArrayBlocks.unary_con(
                tree.value,
                self.get_array_from_tree(tree.left)
            )
        return ArrayBlocks.binary_con(
            tree.value,
            self.get_array_from_tree(tree.left),
            self.get_array_from_tree(tree.right)
        )

    def print(self):
        sb = ""
        for row in self.array:
            for item in row:
                if item == " ":
                    sb += " "
                elif item == "+":
                    sb += "+"
                else:
                    sb += str(chr(item))[0]
            sb += "\n"
        print(sb)

    def html_cell_content(self, cell):
        if cell == "+":
            return """
                <div class="tree_trunk">
                </div>
            """
        elif cell == " ":
            return """
                <div class="empty">
                </div>
            """
        else:
            return f"""
                <div class="tree_node">
                    {str(cell)}
                </div>
            """

    def html_table_cells(self, row):
        cols = []
        for item in row:
            cols.append(f"<td>{self.html_cell_content(item)}</td>\n")
        return cols

    def html_table_rows(self):
        new_line = "\n"
        rows = []
        for row in self.array:
            rows.append(f"<tr>{new_line.join(self.html_table_cells(row))}</tr>")
        return rows

    def create_html(self):
        return """
            <!doctype html>
            <html>
            <head>
                <title>TreeDisplay</title>
                <style>
                    td {
                        padding: 0px;
                        height: inherit;
                        vertical-align: bottom;
                    }
                    table {
                        border-spacing: 0px;
                    }
                    .tree_trunk {
                        min-width: 4px;
                        min-height: 4px;
                        width: 100%;
                        height: 100%;
                        background: #999999;
                    }
                    .tree_node {
                        padding: 1px;
                        font-size: 4pt;
                        background: #aa0000;
                        color: #ffffff;
                    }
                    .empty {
                        min-width: 1px;
                        min-height: 1px;
                    }
                </style>
            </head>
            <body>
                <table>
                    """ + "\n".join(self.html_table_rows()) + """
                </table>
            </body>
            </html>
        """

    # UNCOMMENT IF YOU WANT TO SEE PRINT
    def display2(self):
        self.print()

def display_tree(tree):
    TreeDisplayArrayHTML(tree).display()


def main():
    tree = BinaryTree(0)
    for i in range(256):
        tree.insert(random.randint(33, 127))
    disp = TreeDisplayArrayHTML(tree)
    disp.display2()


if __name__ == '__main__':
    main()
