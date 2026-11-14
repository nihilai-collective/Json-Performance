
----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1669.95 | 0.0387861 | 988.48ms | 4669 | 1280 | 1369 | 2666.38 | 0.150376 | 3.13054 | 12.9334 | 2.58771 | 0.00185599 | 2.02466e-05 | 6.69308e-07 | 1(Win) | true |
| simdjson (ondemand) | 1613.76 | 0.057859 | 1000.03ms | 4669 | 1280 | 3262.26 | 2759.2 | 0.16576 | 3.23793 | 14.4448 | 2.32876 | 0.00128457 | 2.44297e-05 | 3.01189e-06 | 2(Loss) | true |
