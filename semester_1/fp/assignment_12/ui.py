from backtracking import get_payments, get_payments_iter


def run():
    coins_raw = input('Input coins (comma separated): ')
    try:
        coins = [int(x) for x in coins_raw.split(',')]

    except ValueError:
        print('Invalid coins.')
        return

    sum_raw = input('Input sum: ')

    try:
        coins_sum = int(sum_raw)

    except ValueError:
        print('Invalid sum.')
        return

    payments = get_payments_iter(coins, coins_sum)
    print(payments)


run()
