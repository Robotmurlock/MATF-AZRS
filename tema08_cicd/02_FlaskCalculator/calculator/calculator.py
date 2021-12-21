from typing import Union, Callable

Number = Union[int, float]


class Calculator:
    def __init__(self, integers_only: bool = False):
        self.integers_only = integers_only

    def add(self, x: Number, y: Number) -> Number:
        return x + y

    def sub(self, x: Number, y: Number) -> Number:
        return x - y

    def mul(self, x: Number, y: Number) -> Number:
        return x * y
    
    def div(self, x: Number, y: Number) -> Number:
        if y == 0:
            raise ZeroDivisionError('Right operand must not be zero!')
        if self.integers_only:
            return x // y
        else:
            return x / y

    def mod(self, x: Number, y: Number) -> Number:
        if not self.integers_only:
            raise ValueError('Can\'t use mod operations for floats!')
        return x % y

    def _evaluate_from_name(self, operation: str, x: Number, y: Number) -> Number:
        if operation == '+':
            return self.add(x, y)
        elif operation == '-':
            return self.sub(x, y)
        elif operation == '*':
            return self.mul(x, y)
        elif operation == '/':
            return self.div(x, y)
        elif operation == '%':
            return self.mod(x, y)
        else:
            raise ValueError('Unknown operation!')

    def evaluate(self, operation: str, x_str: str, y_str: str) -> Number:
        x, y = (int(x_str), int(y_str)) if self.integers_only else (float(x_str), float(y_str))
        return self._evaluate_from_name(operation, x, y)
        
