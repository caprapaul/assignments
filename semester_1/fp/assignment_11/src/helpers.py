def get_next_gap(gap):
    gap //= 1.3

    if gap < 1:
        return 1

    return int(gap)


def sort_list(items, compare=lambda x, y: x > y):
    """
    Sorts a list. (using comb sort)
    :param items: the list to sort
    :param compare: the comparison function
    :return items_copy: the sorted list
    """
    items_copy = items.copy()
    gap = len(items_copy)

    ok = False

    while gap != 1 or not ok:
        gap = get_next_gap(gap)
        ok = True

        for i in range(0, len(items_copy) - gap):
            if compare(items_copy[i], items_copy[i + gap]):
                items_copy[i], items_copy[i + gap] = items_copy[i + gap], items_copy[i]
                ok = False

    return items_copy


def filter_list(items, accept=lambda item: True):
    """
    Filters a list.
    :param items: the list to filter
    :param accept: the acceptance function
    :return filtered_items: the filtered list
    """
    filtered_items = []

    for item in items:
        if accept(item):
            filtered_items.append(item)

    return filtered_items
