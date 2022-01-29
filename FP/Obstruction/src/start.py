from src.ui.ui import UI

done = False
while not done:
    try:
        rows = int(input("Give number of rows: "))
        cols = int(input("Give number of columns: "))
        if rows < 0 or cols < 0:
            raise ValueError("Invalid size")
        ui = UI(rows, cols)
        ui.start()
        done = True
    except Exception as err:
        print("ERROR! " + str(type(err).__name__) + ': ' + str(err) + '\n')
        input("Press any key to continue...\n")
