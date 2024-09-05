from tasks import format_text


def test_format_text_male():
    person_1 = ['Андрей', 'Попов', 31, 10, 1999, 'М']
    assert format_text(person_1) == "Андрей Попов является мужчиной 1999 г. рождения. Возраст: 24"
    
    
def test_format_text_female():
    person_2 = ['Дарина', 'Романова', 29, 2, 1970, 'Ж']
    assert format_text(person_2) == "Дарина Романова является женщиной 1970 г. рождения. Возраст: 54"
