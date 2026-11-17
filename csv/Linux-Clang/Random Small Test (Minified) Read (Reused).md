
----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2147.02 | 0.13381 | 1021.94ms | 5094 | 2560 | 23467.1 | 2262.68 | 0.0583168 | 2.39762 | 10.9613 | 1.87809 | 0.0005979 | 7.57632e-05 | 3.02899e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1879.22 | 0.129145 | 1060.09ms | 5094 | 2560 | 28533.8 | 2585.12 | 0.157505 | 2.73582 | 12.2419 | 2.08697 | 0.00122594 | 0.000148152 | 8.18978e-05 | 2(Loss) | true |
| Glaze | 1640.14 | 0.0772277 | 1097.01ms | 5094 | 4890 | 25586.5 | 2961.95 | 0.0423225 | 3.12734 | 13.126 | 2.43502 | 0.00414984 | 4.72909e-05 | 9.23337e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1006.07 | 0.181818 | 1287.28ms | 5094 | 320 | 24665.5 | 4828.72 | 0.102407 | 5.07236 | 19.7689 | 3.22183 | 0.00382926 | 3.80349e-05 | 8.58854e-06 | 4(Loss) | true |
