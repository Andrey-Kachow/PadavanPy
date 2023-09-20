'''
    A person knows theirs age and what grade they go to school,
    but can't remember at what age they joined the first grade.

    The program has to find the person's age when they joined the first grade.

    INPUT:
        number representing the age
        number representing current grade

    OPUTPUT:
        Age when the first school grade was joined.
'''

print("How old are you?")
answer = input()

age = int(answer)

print("In what grade do you study")
answer = input()

grade_now = int(answer)

first_grade_age = age - grade_now + 1

print("You have joined the first grade when you were", first_grade_age)