import json, re, os

ENGLISH = "en"
RUSSIAN = "ru"
BRACKETS = [r"{@@@", r"@@@}"]


def bracketed(regex):
    return BRACKETS[0] + " " + regex + " " + BRACKETS[1]


RE_PATTERN = bracketed(r'(.*)')


def strings_json_file(lang):
    return f"strings_{lang}.json"


def format_template(template, strings):
    matches = re.findall(RE_PATTERN, template)
    for match in matches:
        template = template.replace(bracketed(match), strings[match])
    return template


def render(html_path, strings_folder_path, lang):
    with open(os.path.join(strings_folder_path, strings_json_file(lang))) as strings:
        with open(html_path) as template:
            return format_template(template.read(), json.loads(strings.read()))


def test():
    try:
        os.remove("ru.html")
        os.remove("en.html")
    except Exception as e:
        pass
    with open("ru.html", "w") as f:
        f.write(render("index.html", ".", RUSSIAN))
    with open("en.html", "w") as f:
        f.write(render("index.html", ".", ENGLISH))
    import webbrowser
    webbrowser.open('file://' + os.path.realpath('ru.html'))
    webbrowser.open('file://' + os.path.realpath('en.html'))

test()
