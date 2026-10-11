from flask import Flask, request

app = Flask(__name__)

# a simple page that says hello
@app.route('/hello')
def hello():
    print(request.args)
    return "Hello World"
