from flask import Flask
from flask import render_template

#Iniciando a aplicação
app = Flask(__name__)

@app.route('/api/ranking')
def ranking():
    return "Ranking atual"

@app.route('/api/<id>')
def medicao(id):
    return "Cria tabela com o id"

@app.route('/')
def home():
    return "Home."