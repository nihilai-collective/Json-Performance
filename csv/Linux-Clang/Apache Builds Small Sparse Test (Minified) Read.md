
----
### Apache Builds Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3144.73 | 0.0595776 | 798.609ms | 2632 | 1280 | 289.456 | 798.184 | 0.2332 | 1.72073 | 6.87462 | 1.23708 | 0.000919572 | 3.35415e-05 | 3.2651e-06 | 1(Win) | true |
| simdjson (ondemand) | 2410.81 | 0.0609275 | 822.783ms | 2632 | 4890 | 1967.81 | 1041.17 | 0.0632546 | 2.21769 | 8.24582 | 1.35372 | 0.00325341 | 4.62298e-05 | 1.52286e-05 | 2(Loss) | true |
