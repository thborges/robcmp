#
# This program converts a svd file
# into the types needed to programm
# the board using the Robotics Language
#
# Author: Thiago Borges de Oliveira <thborges@gmail.com>
# Date: 24-Jun-2024
#

import sys
import re
import xml.etree.ElementTree as ET

tree = ET.parse(sys.argv[1])
root = tree.getroot()

header = """
/*
 * Part of the Robotics Language Standard Library, under the
 * Apache License v2.0.
 *
 * This file was machine generated from %s. Don't edit.
 */
""" % sys.argv[1]
print(header)

peripheral_header = """
/* Types and registers for {name} {desc} */
"""

template_type = """\
 type {type}_t {{
{fields}
 }}
"""

template_register = """\
 // {prefix_desc}{description}
 register {type}_t {prefix_name}{name} at {addr};
"""

template_field = "\t{name:<xxlenxx} = {type:<20}// {description}"

def clear_description(string):
    return " ".join(string.split())
    
def get_type_for_size(size):
    if size <= 8:
        return 'uint8'
    elif size <= 16:
        return 'uint16'
    elif size <= 32:
        return 'uint32'
    else:
        return 'uint64'


def get_field_for_type(string):
    bits = re.search(r"\[(\d+):(\d+)\]", string)
    field = {}
    field['start'] = int(bits.group(2))
    field['end'] = int(bits.group(1))
    size = field['end'] - field['start'] + 1
    if size == 1:
        field['type'] = 'false;'
    else:
        field['type'] = 'uint' + str(size) + '(0);'
    return field


def add_reserved(reservedfields, start, size, resnum):
    first = True
    orig_size = size
    while size > 0:
        fsize = 0
        if size == 1:
            ftype = "false;"
            fsize = 1
        elif size in [2,3,4,5,6,7,8]:
            ftype = "uint%d(0);" % size
            fsize = size
        elif size >= 32:
            ftype = "uint32(0);"
            fsize = 32
        elif size >= 16:
            ftype = "uint16(0);"
            fsize = 16
        elif size > 8:
            ftype = "uint8(0);"
            fsize = 8
        fres = {}
        fres['name'] = '_res%d' % resnum
        if first:
            fres['description'] = 'Reserved, %d bits' % (orig_size,)
            first = False
        else:
            fres['description'] = ''
        fres['type'] = ftype
        fres['start'] = start
        start = start + fsize
        size = size - fsize
        resnum = resnum + 1;
        reservedfields.append(fres)
    return resnum


def get_fields_str(fields_node, size):
    if fields_node == None:
        return ""
    
    fields = []
    for field_node in fields_node.iter('field'):
        bitRange = field_node.find('bitRange')
        if bitRange == None:
            bitOffset = field_node.find('bitOffset').text
            bitWidth = field_node.find('bitWidth').text
            bitRange = "[%d:%s]" % (int(bitOffset) + int(bitWidth)-1, bitOffset)
        else:
            bitRange = bitRange.text
        field = get_field_for_type(bitRange)
        field['name'] = field_node.find('name').text

        field['description'] = ''
        description_node = field_node.find('description')
        if description_node is not None:
            field['description'] = clear_description(description_node.text)

        fields.append(field)

    fields = sorted(fields, key=lambda field: field['start'])

    # add missing fields as reserved
    reservedfields = []
    i = 0
    resnum = 1
    for f in fields:
        if f['start'] > i:
            #print("start: %d, i: %d\n" % (f['start'], i))
            resnum = add_reserved(reservedfields, i, f['start']-i, resnum)
        i = f['end'] + 1

    # missing bits at end
    if i < size:
        add_reserved(reservedfields, i-1, size-i, resnum)

    fields = fields + reservedfields
    maxlen = max([len(f['name']) for f in fields])
    custom_template_field = template_field.replace('xxlenxx', str(maxlen))
    fields = sorted(fields, key=lambda field: field['start'])
    return "\n".join([custom_template_field.format(**f) for f in fields])


# map dependencies to generate peripherals prefixes
derived = {}
for peripheral in root.iterfind('.//peripheral[@derivedFrom]'):
    name = peripheral.find('name').text
    derivedFrom = peripheral.attrib['derivedFrom']
    derived[name] = derivedFrom
    # register the inherited peripheral to prefix it latter
    derived[derivedFrom] = derivedFrom


# map repeated register names
repeated_regs = {}
for register in root.iterfind('.//register'):
    name = register.find('name').text
    if name in repeated_regs:
        repeated_regs[name] = True
    else:
        repeated_regs[name] = False


# generate code!
def print_tags(tags):
    for t in tags:
        node = root.find(t)
        if node is not None:
            print("\t%s: %s" % (t, node.text))

print("/*")
print_tags(['vendor', 'name', 'series', 'version', 'description'])
print("*/")

for peripheral in root.iter('peripheral'):
    # peripheral name
    pname = peripheral.find('name').text
    
    # peripheral description
    pdesc_node = peripheral.find('description')
    pdesc = ''
    if pdesc_node is not None:
        pdesc = "\n  " + clear_description(pdesc_node.text) + "\n"
    
    # peripheral base address
    baseAddr = peripheral.find('baseAddress').text

    # print peripheral header
    print(peripheral_header.format(name=pname,desc=pdesc))

    # prefix base and derived peripherals registers
    prefix_name = ''
    prefix_desc = ''
    if pname in derived:
        prefix_name = pname + "_"
        prefix_desc = pname + " "

    # loop through base registers
    registers = None
    isDerived = False
    if (pname in derived) and (derived[pname] != pname):
        isDerived = True
        # change the peripheral to the inherited one
        peripheral = root.find(".//peripheral[name = '%s']" % derived[pname])

    for register in peripheral.iter('register'):
        regdata = {}
        regdata['prefix_desc'] = prefix_desc
        regdata['prefix_name'] = prefix_name
        regdata['name'] = register.find('name').text

        if repeated_regs[regdata['name']] and not isDerived:
            # The register being created exists in more than one peripheral
            # Thus, we prefix it with the peripheral name
            regdata['name'] = pname + '_' + regdata['name']

        if isDerived:
            original_register = register.find('name').text
            inherited_name = ''
            if repeated_regs[original_register]:
                inherited_name = peripheral.find('name').text + "_"
            regdata['type'] = inherited_name + register.find('name').text
        else:
            regdata['type'] = regdata['name']

        regdata['description'] = ''
        description_node = register.find('description')
        if description_node is not None:
            regdata['description'] = clear_description(description_node.text)
        
        offset = register.find('addressOffset').text
        intoffset = int(offset, 16)
        if intoffset == 0:
            regdata['addr'] = "%s" % (baseAddr)
        else:
            intaddr = int(baseAddr, 16) + intoffset
            regdata['addr'] = "%#x" % (intaddr)

        # print register tree
        size = 0
        size_node = register.find('size')
        if size_node is not None:
            size = int(size_node.text, 0)

        fields = register.find('fields')
        if fields == None:
            regdata['type'] = get_type_for_size(size)
            print(template_register.format(**regdata))
        else:
            if not isDerived:
                regdata['fields'] = get_fields_str(fields, size)
                print(template_type.format(**regdata))
            print(template_register.format(**regdata))

