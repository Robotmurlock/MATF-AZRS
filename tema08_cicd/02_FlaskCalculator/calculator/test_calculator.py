import unittest
from calculator import Calculator

class TestCalculator(unittest.TestCase):
    def setUp(self):
        self.calculator = Calculator()
        self.int_calculator = Calculator(True)

    def test_add_integer(self):
        # Arrange (er - expected result, r - result)
        x1, y1, er1 = 2, 3, 5
        x2, y2, er2 = 10, 11, 21

        # Act
        r1 = self.int_calculator.add(x1, y1)
        r2 = self.int_calculator.add(x2, y2)

        # Assert
        self.assertEqual(er1, r1)
        self.assertEqual(er2, r2)

    def test_evaluate_integer(self):
        # Arrange
        x1, y1, op1, er1 = '2', '3', '+', 5
        x2, y2, op2, er2 = '10', '11', '-', -1

        # Act
        r1 = self.int_calculator.evaluate(op1, x1, y1)
        r2 = self.int_calculator.evaluate(op2, x2, y2)

        # Assert
        self.assertEqual(er1, r1)
        self.assertEqual(er2, r2) 
        

if __name__ == '__main__':
    unittest.main()
