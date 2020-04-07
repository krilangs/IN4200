import matplotlib.pyplot as plt
import numpy as np

fonts = {"font.size": 14}
plt.rcParams.update(fonts)

threads = np.linspace(1,12,12)

counts = [2.9995,2.8333,1.9995,2.3332,2.4997,2.5664,2.1665,2.1653,2.7433,2.6665,\
          2.9998,2.4997]

sorts = [10.3976,8.5137,7.8227,7.1658,7.8331,2.1662,0.9995,0.9993,1.3340,1.1662,\
         1.4995,1.1661]

plt.figure()
plt.title("Timing of count_mutual_links2 parallel\n as function of threads")
plt.plot(threads, counts)
plt.xlabel("No. of threads")
plt.ylabel("Time [ms]")
plt.tight_layout()
plt.savefig("Time_count.png")

plt.figure()
plt.title("Timing of top_n_webpages parallel\n as function of threads")
plt.plot(threads, sorts)
plt.xlabel("No. of threads")
plt.ylabel("Time [ms]")
plt.tight_layout()
plt.savefig("Time_sort.png")

plt.show()