string = '''<svg height="210" width="400">
<path d="M150 0 L75 200 L225 200 Z" />
</svg>'''


with open('workfile.svg', 'w') as f:
	f.write(string)
