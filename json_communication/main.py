#!flask/bin/python

import sys

from flask import Flask, render_template, request, redirect, Response, jsonify
import random, json

app = Flask(__name__)

@app.route('/')
def output():
	# serve index template
	return render_template('index.html', name='Joe')

@app.route('/receiver', methods = ['POST'])
def worker():
	# read json + reply
	data = request.get_json(silent=True)
	result = ''

	for item in data:
		# loop over every row
		make = str(item['make'])
		if(make == 'Porsche'):
			result += make + ' -- That is a good manufacturer\n'
		else:
			result += make + ' -- That is only an average manufacturer\n'

	return result

@app.route('/receiver2', methods = ['POST'])
def worker2():
	json_response = {"chave": ["valor1", "valor2"]}
	return jsonify(json_response)
	#return json.dumps(json_response)

if __name__ == '__main__':
	# run!
	app.run("0.0.0.0", "5000")
