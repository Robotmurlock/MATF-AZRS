from flask import Flask, render_template, request
from calculator.calculator import Calculator
import sys

Flask_App = Flask(__name__) # Creating our Flask Instance
calculator = Calculator()

@Flask_App.route('/ping', methods=['GET'])
def ping():
    return {'success': True}

@Flask_App.route('/', methods=['GET'])
def index():
    """ Displays the index page accessible at '/' """

    return render_template('index.html')

@Flask_App.route('/operation_result/', methods=['POST'])
def operation_result():
    """Route where we send calculator form input"""

    error = None
    result = None

    # request.form looks for:
    # html tags with matching "name= "
    first_input = request.form['Input1']  
    second_input = request.form['Input2']
    operation = request.form['operation']

    try:
        result = calculator.evaluate(operation, first_input, second_input)

        return render_template(
            'index.html',
            input1=first_input,
            input2=second_input,
            operation=operation,
            result=result,
            calculation_success=True
        )
        
    except ZeroDivisionError:
        return render_template(
            'index.html',
            input1=first_input,
            input2=second_input,
            operation=operation,
            result="Bad Input",
            calculation_success=False,
            error="You cannot divide by zero"
        )
        
    except ValueError:
        return render_template(
            'index.html',
            input1=first_input,
            input2=second_input,
            operation=operation,
            result="Bad Input",
            calculation_success=False,
            error="Cannot perform numeric operations with provided input"
        )

if __name__ == '__main__':
    Flask_App.debug = True
    Flask_App.run(host='0.0.0.0')
