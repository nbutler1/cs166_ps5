import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties

with open('results.txt', 'rb') as f:
    data = f.readlines()

# Set initial variables
colors = ['r-', 'b-', 'g-', 'c-', 'm-', 'y-', 'k-', 'w-']
curr_filter = ''

# Set to false to indicate we have not started graphing yet...
graphing = False
x_insert = []
x_query = []
y = []
leg = []
inserts = []
queries = []
loads = []


# loop through data
for line in data:
    line = line.strip()
    # Case 1: New filter, reset shit
    if str.startswith(line, '#### Timing'):
        curr_filter = line
        curr_filter = curr_filter.replace('#### Timing', '')
        curr_filter = curr_filter.replace(' ####', '')
        curr_filter.strip()
        graphing = True
        x_insert, x_query, y, leg = [], [], [], []
        inserts, queries, loads = [], [], []
        continue
    # Case 2: New hash type, write out current and reset
    if graphing and str.startswith(line, '==='):
        if len(x_query) != 0:
            queries.append(x_query)
            inserts.append(x_insert)
            loads.append(y)
        x_insert, x_query, y = [], [], []
        filt = line
        filt = filt.replace('===', '')
        filt = filt.replace('ependent Polynomial Hash', '')
        filt = filt.replace('ependent Tabulation Hash', ' Tab')
        filt = filt.replace('Hash', '')
        filt.strip()
        leg.append(filt)
        continue
    # Case 3: Load Factor, add to y
    if graphing and str.startswith(line, '--- Load'):
        val = line.replace('--- Load Factor:', '')
        val = val.replace('---', '')
        val.strip()
        y.append(float(val))
        continue
    # Case 4: Insertion
    if graphing and str.startswith(line, 'Insertion'):
        line = line.replace('ns / op', '')
        line = line.replace('Insertion:', '')
        x_insert.append(float(line.strip()))
        continue
    # Case 5: Query:
    if graphing and str.startswith(line, 'Query'):
        line = line.replace('ns / op', '')
        line = line.replace('Query:', '')
        x_query.append(float(line.strip()))
        continue
    # Case 6: end of filter, save shit
    if graphing and str.startswith(line, '##############'):
        queries.append(x_query)
        inserts.append(x_insert)
        loads.append(y)
        plt.subplot(2, 1, 1)
        fontP = FontProperties()
        fontP.set_size('small')
        for i in range(len(inserts)):
            plt.plot(loads[i], inserts[i], colors[i], label = leg[i])
        plt.title('Insert Times for ' + curr_filter)
        plt.ylabel('Time in ns / op')
        #plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3,
        #                       ncol=2, mode="expand", borderaxespad=0.)
        plt.legend(prop = fontP)
        plt.subplot(2, 1, 2)
        #plt.xlim([0.3, 0.55])
        for j in range(len(queries)):
            plt.plot(loads[j], queries[j], colors[j])
        plt.xlabel('Load Factor')
        plt.ylabel('Time in ns / op')
        plt.title('Query Times for ' + curr_filter)
        curr_filter = curr_filter.strip()
        curr_filter = curr_filter.replace(' ', '_')
        plt.savefig(curr_filter + '.png')
        plt.clf()


