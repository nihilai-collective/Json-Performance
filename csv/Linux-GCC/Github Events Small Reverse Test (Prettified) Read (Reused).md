
----
### Github Events Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1228.74 | 0.04866 | 896.397ms | 2158 | 4890 | 3248.13 | 1674.91 | 0.102541 | 4.26807 | 15.753 | 3.05792 | 0.00178695 | 9.34365e-05 | 4.24539e-05 | 1(Win) | true |
| simdjson (ondemand) | 990.601 | 0.0695096 | 954.75ms | 2158 | 640 | 1334.67 | 2077.56 | 0.142092 | 5.29983 | 20.6909 | 3.93837 | 0.00134239 | 7.02329e-05 | 7.96455e-06 | 2(Loss) | true |
