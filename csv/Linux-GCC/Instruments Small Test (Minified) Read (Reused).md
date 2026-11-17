
----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1674.21 | 0.123734 | 994.406ms | 4669 | 320 | 3465.43 | 2659.59 | 0.00235004 | 3.11917 | 12.9321 | 2.58771 | 0.00173619 | 2.14179e-05 | 6.69308e-07 | 1(Win) | true |
| simdjson (ondemand) | 1625.06 | 0.0363467 | 1002.01ms | 4669 | 4890 | 4850.08 | 2740.03 | 0.202161 | 3.20141 | 14.4097 | 2.3097 | 0.000431292 | 3.29371e-05 | 5.56251e-06 | 2(Loss) | true |
