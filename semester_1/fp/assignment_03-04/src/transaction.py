class Transaction:
    def __init__(self, day: int, money_amount: int, type: str, description: str):
        self.__day = day
        self.__money_amount = money_amount
        self.__type = type
        self.__description = description

    def get_day(self):
        return self.__day

    def set_day(self, value: int):
        self.__day = value

    def get_money_amount(self):
        return self.__money_amount

    def set_money_amount(self, value: int):
        self.__money_amount = value

    def get_type(self):
        return self.__type

    def set_type(self, value: str):
        self.__type = value

    def get_description(self):
        return self.__description

    def set_description(self, value: str):
        self.__description = value
