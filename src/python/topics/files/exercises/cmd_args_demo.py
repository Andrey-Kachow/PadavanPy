import sys

print("Вы ввели команду:")
print()
print("python " + " ".join(sys.argv))
print()
print(f"Название исполняемого файла: {sys.argv[0]}")
print("Остальные аргументы командной строки: " +\
    (" ".join(sys.argv[1:]) if len(sys.argv) > 1 else "А их на этот раз нет. Аргумент всего один"))
print()
print(f"sys.argv равен значению {sys.argv}")
print()
print("Чтобы получить доступ к аргументам, необходимо импортировать модуль sys")
print("Вот так:")
print()
print("import sys")
print()
print("Затем к каждому аргументу можно получить доступ следующим образом")
print()

count = 0
for arg in sys.argv:
    print(f"sys.argv[{count}] -----> '{arg}'")
    count += 1

print()
print("Поздравляем! Теперь вы научились заниматься обработкой аргументов командной строки!")
