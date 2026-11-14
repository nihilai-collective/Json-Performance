
----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2453.58 | 0.0606873 | 1047.49ms | 7932 | 2560 | 8961.89 | 3083.06 | 0.00278749 | 2.08951 | 9.72832 | 1.37658 | 0.00056225 | 4.37311e-05 | 2.15208e-05 | 1(Win) | true |
| Jsonifier (generic) | 2424.9 | 0.136774 | 1053.56ms | 7932 | 80 | 1456.38 | 3119.53 | 0.0160255 | 2.15252 | 9.01488 | 1.70222 | 0.00118507 | 2.04866e-05 | 1.5759e-06 | 2(Loss) | true |
