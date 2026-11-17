
----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1750.41 | 0.0320444 | 846.105ms | 2158 | 4890 | 694.127 | 1175.74 | 0.0223513 | 3.06959 | 11.0783 | 2.07507 | 0.000465572 | 0.000119212 | 4.86135e-05 | 1(Win) | true |
| simdjson (ondemand) | 1686.44 | 0.0466192 | 845.759ms | 2158 | 4890 | 1582.71 | 1220.34 | 0.211095 | 3.17884 | 12.164 | 1.98749 | 0.000483766 | 9.44789e-05 | 3.11771e-05 | 2(Loss) | true |
