from flask import Flask, render_template, request, redirect, url_for, session
from pymongo import MongoClient
import os
from dotenv import load_dotenv

app = Flask(__name__)
app.secret_key = os.getenv('FLASK_SECRET_KEY')

load_dotenv()

mongo_uri = os.getenv('MONGO_URI')

client = MongoClient(mongo_uri)
db = client.get_database()

sensor_data_collection = db['sensor_data']
user_collection = db['users']
contact_collection = db['contact_messages']

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if user_collection.find_one({'username': username}):
            return render_template('register.html', error='Username already exists')
        user_collection.insert_one({'username': username, 'password': password})
        return redirect(url_for('login'))
    return render_template('register.html')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = user_collection.find_one({'username': username, 'password': password})
        if user:
            session['username'] = username
            return redirect(url_for('ponds'))
        else:
            return render_template('login.html', error='Invalid username or password')
    return render_template('login.html')

@app.route('/logout')
def logout():
    session.pop('username', None)
    return redirect(url_for('login'))

@app.route('/ponds')
def ponds():
    return render_template('ponds.html', username=session['username'])

@app.route('/dashboard/<int:pond_id>')
def dashboard(pond_id):
    if 'username' in session:
        sensor_data = sensor_data_collection.find_one({'pond_id': pond_id})
        if sensor_data:
            temperature = sensor_data.get('temperature')
            ph_value = sensor_data.get('ph_value')
            water_level = sensor_data.get('water_level')
            return render_template('dashboard.html', username=session['username'], temperature=temperature, ph_value=ph_value, water_level=water_level)
        else:
            return render_template('dashboard.html', username=session['username'], error='No sensor data available for this pond')
    else:
        return redirect(url_for('login'))

@app.route('/about')
def about():
    return render_template('about.html')

@app.route('/contact', methods=['GET', 'POST'])
def contact():
    if request.method == 'POST':
        name = request.form['name']
        email = request.form['email']
        message = request.form['message']
        contact_collection.insert_one({'name': name, 'email': email, 'message': message})
        return redirect(url_for('contact'))
    return render_template('contact.html')

@app.route('/')
def index():
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')
