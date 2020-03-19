class ExpenseError(Exception):
    def __init__(self, message):
        super().__init__(message)


class Expense:
    def __init__(self, day: int, money_amount: int, type: str):
        if day < 1 or day > 30:
            raise ValueError('Invalid day: value must be between 1 and 30.')

        self.__day = day
        self.__money_amount = money_amount
        self.__type = type

    @property
    def day(self):
        return self.__day

    @property
    def money_amount(self):
        return self.__money_amount

    @property
    def type(self):
        return self.__type
