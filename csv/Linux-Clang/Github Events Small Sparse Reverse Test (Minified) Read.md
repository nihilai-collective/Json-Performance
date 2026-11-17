
----
### Github Events Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3322.94 | 0.157864 | 762.439ms | 1691 | 160 | 93.9143 | 485.312 | 0.0180264 | 1.7063 | 6.86339 | 1.21644 | 0.000683767 | 2.21762e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2592.6 | 0.280254 | 779.858ms | 1691 | 80 | 243.113 | 622.025 | 0.144898 | 2.15107 | 8.66588 | 1.4317 | 0.00100532 | 1.47842e-05 | 0 | 2(Loss) | true |
