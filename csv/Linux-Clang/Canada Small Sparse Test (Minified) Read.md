
----
### Canada Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7510.91 | 0.118665 | 770.323ms | 4630 | 2560 | 1245.83 | 587.88 | 0.566616 | 0.731142 | 3.63391 | 0.469979 | 0.000435171 | 1.82235e-05 | 3.20599e-06 | 1(Win) | true |
| simdjson (ondemand) | 6600.23 | 0.0306619 | 776.367ms | 4630 | 4890 | 205.755 | 668.993 | 0.381041 | 0.827528 | 4.09914 | 0.490497 | 0.000432142 | 1.44872e-05 | 1.45755e-06 | 2(Loss) | true |
