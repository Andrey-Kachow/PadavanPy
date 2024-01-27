import os 

from flask import Flask, request

# pip3 install flask
# flask --app run
messages=[]

def create_app(test_config=None):
    # create and configure the app
    app = Flask(__name__)

    # a simple page that says hello
    @app.route('/hello')
    def hello():

        print(request.args)

        if "message" in request.args:
            incoming_message = request.args["message"]
            messages.append(incoming_message)
        else:
            incoming_message = ""

        messages_text ='<br>'.join(messages)

        return f"""
    <!DOCTYPE html>
    <html>
    <body>

    <h1>Enter Your Message</h1>

    <p>
        {messages_text}
    </p>

    <form action="/hello">
    <label for="message">Enter Text:</label>
    <input type="text" id="message" name="message"><br><br>
    <input type="submit" value="Submit">
    </form>

    </body>
    </html>
"""

    return app