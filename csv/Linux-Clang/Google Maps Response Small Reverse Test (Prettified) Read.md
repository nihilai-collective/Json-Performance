
----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1507.68 | 0.0496365 | 1314.86ms | 9378 | 320 | 2774.32 | 5932.01 | 0.0428474 | 3.44017 | 14.9562 | 2.92163 | 0.00621468 | 1.033e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1441.86 | 0.0708021 | 1340.86ms | 9378 | 80 | 1542.97 | 6202.8 | 0.0181337 | 3.59663 | 16.0671 | 2.86788 | 0.0044799 | 3.33227e-05 | 3.99872e-06 | 2(Loss) | true |
