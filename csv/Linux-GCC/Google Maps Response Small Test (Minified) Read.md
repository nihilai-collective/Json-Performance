
----
### Google Maps Response Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1429.43 | 0.0430107 | 1022.47ms | 4390 | 4890 | 7760.13 | 2928.89 | 0.00832266 | 3.64735 | 16.733 | 3.16743 | 0.00143555 | 5.28716e-05 | 1.84468e-05 | 1(Win) | true |
| simdjson (ondemand) | 1097.86 | 0.064006 | 1107.49ms | 4390 | 1280 | 7625.75 | 3813.43 | 0.069668 | 4.67459 | 19.2125 | 3.55854 | 0.00322252 | 5.48121e-05 | 2.63383e-05 | 2(Loss) | true |
