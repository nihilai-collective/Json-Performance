
----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2372.26 | 0.0600987 | 822.034ms | 2632 | 4890 | 1977.37 | 1058.09 | 0.0170388 | 2.24578 | 9.32371 | 1.7424 | 0.000953267 | 3.28659e-05 | 8.93518e-06 | 1(Win) | true |
| simdjson (ondemand) | 2107.51 | 0.0898719 | 835.048ms | 2632 | 80 | 91.6581 | 1191.01 | 0.00104954 | 2.52525 | 9.87006 | 1.76026 | 0.00134403 | 0 | 0 | 2(Loss) | true |
