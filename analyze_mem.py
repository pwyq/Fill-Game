import sys

new_f = open(sys.argv[1], 'r')
old_f = open(sys.argv[2], 'r')

print(f"\nAnalyzing {sys.argv[1]} and {sys.argv[2]} ...")

new_lines = [l.rstrip() for l in new_f.readlines()]
old_lines = [l.rstrip() for l in old_f.readlines()]

new_f.close(); old_f.close()

pairs = [(n,o) for n,o in zip(new_lines, old_lines)]
mem_pairs = pairs[1::3]
ratios = [float(n)/float(o) for n,o in mem_pairs]

avg = sum(ratios)/len(ratios)

print(f"Average mem change: new/old = {avg}\n")