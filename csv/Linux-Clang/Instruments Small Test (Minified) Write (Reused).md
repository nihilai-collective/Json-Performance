
----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13690.9 | 0.233943 | 767.586ms | 4669 | 4890 | 2830.83 | 325.232 | 0.203269 | 0.417659 | 1.29964 | 0.336689 | 0.000214617 | 3.20611e-05 | 8.67226e-06 | 1(Win) | true |
| Glaze | 2751.17 | 1.46118 | 899.331ms | 4669 | 80 | 44741.5 | 1618.47 | 0.216722 | 1.88472 | 3.1949 | 0.397516 | 0.000214179 | 5.88991e-05 | 2.94496e-05 | 2(Loss) | true |
