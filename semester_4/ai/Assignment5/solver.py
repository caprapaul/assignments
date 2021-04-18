# -*- coding: utf-8 -*-
"""
In this file your task is to write the solver function!

"""

from membership_function import MembershipFunction
from rule import Rule

angle_membership_functions = [
    MembershipFunction('NVB', None, -40, -25),
    MembershipFunction('NB', -40, -25, -10),
    MembershipFunction('N', -20, -10, 0),
    MembershipFunction('ZO', -5, 0, 5),
    MembershipFunction('P', 0, 10, 20),
    MembershipFunction('PB', 10, 25, 40),
    MembershipFunction('PVB', 25, 40, None)
]

speed_membership_functions = [
    MembershipFunction('NB', None, -8, -3),
    MembershipFunction('N', -6, -3, 0),
    MembershipFunction('ZO', -1, 0, 1),
    MembershipFunction('P', 0, 3, 6),
    MembershipFunction('PB', 3, 8, None)
]

force_membership_functions = [
    MembershipFunction('NVVB', None, -32, -24),
    MembershipFunction('NVB', -32, -24, -16),
    MembershipFunction('NB', -24, -16, -8),
    MembershipFunction('N', -16, -8, 0),
    MembershipFunction('Z', -4, 0, 4),
    MembershipFunction('P', 0, 8, 16),
    MembershipFunction('PB', 8, 16, 24),
    MembershipFunction('PVB', 16, 24, 32),
    MembershipFunction('PVVB', 24, 32, None)
]

rule_base = {
    'PVB': {
        'PB': Rule('PVVB'),
        'P': Rule('PVVB'),
        'ZO': Rule('PVB'),
        'N': Rule('PB'),
        'NB': Rule('P'),
    },
    'PB': {
        'PB': Rule('PVVB'),
        'P': Rule('PVB'),
        'ZO': Rule('PB'),
        'N': Rule('P'),
        'NB': Rule('Z'),
    },
    'P': {
        'PB': Rule('PVB'),
        'P': Rule('PB'),
        'ZO': Rule('P'),
        'N': Rule('Z'),
        'NB': Rule('N'),
    },
    'ZO': {
        'PB': Rule('PB'),
        'P': Rule('P'),
        'ZO': Rule('Z'),
        'N': Rule('N'),
        'NB': Rule('NB'),
    },
    'N': {
        'PB': Rule('P'),
        'P': Rule('Z'),
        'ZO': Rule('N'),
        'N': Rule('NB'),
        'NB': Rule('NVB'),
    },
    'NB': {
        'PB': Rule('Z'),
        'P': Rule('N'),
        'ZO': Rule('NB'),
        'N': Rule('NVB'),
        'NB': Rule('NVVB'),
    },
    'NVB': {
        'PB': Rule('N'),
        'P': Rule('NB'),
        'ZO': Rule('NVB'),
        'N': Rule('NVVB'),
        'NB': Rule('NVVB'),
    },
}


def nested_values(d):
    for v in d.values():
        if isinstance(v, dict):
            yield from nested_values(v)
        else:
            yield v


rules_list = list(nested_values(rule_base))


def memberships(x, functions):
    result = {}

    for function in functions:
        v = function.fuzzify(x)
        v = function.fuzzify(x)
        result[function.name] = v

    return result


def solver(t, w):
    """
    Parameters
    ----------
    t : TYPE: float
        DESCRIPTION: the angle theta
    w : TYPE: float
        DESCRIPTION: the angular speed omega

    Returns
    -------
    F : TYPE: float
        DESCRIPTION: the force that must be applied to the cart
    or

    None :if we have a division by zero

    """
    t_memberships = memberships(t, angle_membership_functions)
    w_memberships = memberships(w, speed_membership_functions)

    for t_key in rule_base.keys():
        for w_key in rule_base[t_key].keys():
            value = min(t_memberships[t_key], w_memberships[w_key])
            rule_base[t_key][w_key].value = value

    f_memberships = {}
    for force_function in force_membership_functions:
        function_rules_values = [
            rule.value for rule in rules_list if rule.name == force_function.name]
        membership = max(function_rules_values)
        f_memberships[force_function.name] = membership

    f_memberships_sum = sum(f_memberships.values())

    if f_memberships_sum == 0:
        return None

    force = 0

    for force_function in force_membership_functions:
        force += f_memberships[force_function.name] * force_function.middle

    force /= f_memberships_sum

    return force
