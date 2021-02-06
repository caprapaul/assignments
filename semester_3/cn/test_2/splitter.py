ip = '177.91.107.0'
net_mask = '255.255.255.248'
# (network_name, network_ip_count)
# network_ip_count should include the router, NA and BA ips
networks = [
    ('n1', 240 + 3),
    ('n2', 160 + 3),
    ('n3', 64 + 3),
    ('n4', 64 + 3),
    ('n5', 16 + 3),
    ('n1-5', 5 + 2),
    ('n5w', 2 + 2),
]

# (network_name, server_name)
servers = [
    ('n1', 's1_dhcp'),
    ('n2', 's2_web'),
    ('n3', 's3_dns'),
]

def address_to_int(address):
    return sum(map(lambda x: (int(x[1]) << (8 * x[0])), enumerate(reversed(address.split('.')))))


def int_to_address(value):
    return '.'.join(reversed(list(map(lambda x: str((x[1] & (255 << (8 * x[0]))) >> (8 * x[0])), enumerate(4 * [value])))))


def net_mask_to_size(net_mask):
    return bin(net_mask).count("1")


def size_to_net_mask(value):
    return ((1 << 33) - 1) & ~((1 << (32 - value)) - 1)


def normalize_network(size):
    i = 0
    x = 1

    while x < size:
        i += 1
        x *= 2
    
    return (x, i)


def split_network_recursive(networks, net_address, broadcast_address):
    if broadcast_address - net_address + 1 <= 0:
        return []

    mask_size = 32 - normalize_network(broadcast_address - net_address + 1)[1]

    if len(networks) == 0:
        return [('_', net_address, broadcast_address, size_to_net_mask(mask_size), mask_size)]

    for (i, network) in enumerate(networks):
        (name, size, mask) = network
        
        if mask == mask_size:
            del networks[i]
            return [(name, net_address, broadcast_address, size_to_net_mask(mask_size), mask_size)]

    middle_address = net_address + ((broadcast_address - net_address) // 2)

    return split_network_recursive(networks, net_address, middle_address) + split_network_recursive(networks, middle_address + 1, broadcast_address)



def split_network(networks, net_address, broadcast_address):
    result = []
    result = split_network_recursive(networks, net_address, broadcast_address)
    return result


def sort_networks(networks):
    return sorted(networks, key=lambda x: x[1], reverse=True)

print(int_to_address(size_to_net_mask(29)))


ip_val = address_to_int(ip)
net_mask_val = address_to_int(net_mask)

net_address = ip_val & net_mask_val
broadcast_address = ip_val | (~net_mask_val)

if net_address < 0:
    net_address += 1 << 32

if broadcast_address < 0:
    broadcast_address += 1 << 32

networks = sort_networks(networks)
networks_normalized = []

for network in networks:
    (name, size) = network
    (required_size, power) = normalize_network(size)
    net_mask_type = 32 - power
    networks_normalized.append((name, required_size, net_mask_type))

subnetworks = split_network(networks_normalized, net_address, broadcast_address)

server_addressess = []
for (network_name, server_name) in servers:
    for (name, address, _, _, _) in subnetworks:
        if network_name != name:
            continue

        server_addressess.append((server_name, int_to_address(address + 2)))
        break


server_addressess_strings = list(map(lambda x: f'{x[0]:<14} {x[1]:<8}', server_addressess))
server_addressess_string = '\n'.join([server for server in server_addressess_strings])

subnetworks = list(map(lambda x: (x[0], int_to_address(x[1]), int_to_address(x[2]), int_to_address(x[3]), x[4]), subnetworks))
subnetworks_strings = list(map(lambda x: f'{x[0]:<8} {x[1]:<18} {x[2]:<18} {x[3]:<18} {x[4]:<12}', subnetworks))
subnetworks_string = '\n'.join([str(network) for network in subnetworks_strings])

#print('ip int:', ip_val)
#print('na int:', net_address)
#print('ba int:', broadcast_address)
#print()
print('ip: ', int_to_address(ip_val))
print('netmask: ', int_to_address(size_to_net_mask(net_mask_to_size(net_mask_val))))
print('netmask size:', net_mask_to_size(net_mask_val))
print('na:', int_to_address(net_address))
print('ba:', int_to_address(broadcast_address))
print()
print('subnetworks:')
print('name     network            broadcast          netmask            netmask_size')
print('-------------------------------------------------------------------------------')
print(subnetworks_string)
print()
print('servers:')
print('name           address')
print('-----------------------------')
print(server_addressess_string)