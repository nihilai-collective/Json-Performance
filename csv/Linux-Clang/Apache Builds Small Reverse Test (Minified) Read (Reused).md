
----
### Apache Builds Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1509.23 | 0.156412 | 896.478ms | 2632 | 640 | 4330.97 | 1663.15 | 0.00826676 | 3.4921 | 14.6516 | 2.80509 | 0.00449812 | 3.79939e-05 | 5.3429e-06 | 1(Win) | true |
| simdjson (ondemand) | 793.885 | 0.0445297 | 1044.32ms | 2632 | 2560 | 5074.53 | 3161.76 | 0.0586997 | 6.56705 | 29.117 | 5.49962 | 0.00925211 | 6.76767e-05 | 1.76612e-05 | 2(Loss) | true |
