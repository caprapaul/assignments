def get_payments(coins, s):
    payments = []
    _payments(coins, s, [], payments)
    return payments


def get_payments_iter(coins, s):
    payments = []
    _payments_iter(coins, s, payments)
    return payments


def _check_payment(s, payment):
    payment_sum = 0

    for coin in payment:
        payment_sum += coin

    return s == payment_sum


def _check_payment_overflow(s, payment):
    payment_sum = 0

    for coin in payment:
        payment_sum += coin

    return payment_sum > s


def _check_unique_payment(payment, payments):
    for pay in payments:
        different = False
        for coin in payment:
            if coin not in pay:
                different = True

        for coin in pay:
            if coin not in payment:
                different = True

        if not different:
            return False

    return True


def _payments(coins, s, payment, payments):
    current_payment = list(payment)
    if len(coins) == 0:
        return

    if _check_payment_overflow(s, current_payment):
        return

    if _check_payment(s, current_payment) and _check_unique_payment(current_payment, payments):
        payments.append(current_payment)
        return

    n = len(coins)
    for i in range(n):
        coins_copy = list(coins)
        coin = coins_copy.pop(i)
        current_payment.append(coin)

        _payments(coins_copy, s, current_payment, payments)

        current_payment.remove(coin)

    return


def _payments_iter(coins, s, payments):
    stack = [(coins, [])]

    while len(stack) > 0:
        stack_coins, stack_payment = stack.pop()

        n = len(stack_coins)

        if n == 0:
            continue

        current_payment = list(stack_payment)

        if _check_payment_overflow(s, current_payment):
            continue

        if _check_payment(s, current_payment) and _check_unique_payment(current_payment, payments):
            payments.append(current_payment)
            continue

        for i in range(n):
            coins_copy = list(stack_coins)
            coin = coins_copy.pop(i)
            current_payment.append(coin)

            stack.append((coins_copy, list(current_payment)))

            current_payment.remove(coin)

