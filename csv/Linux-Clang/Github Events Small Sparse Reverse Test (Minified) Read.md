
----
### Github Events Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3388.13 | 0.0779915 | 768.993ms | 1691 | 40 | 5.51218 | 475.975 | 0.012254 | 1.65052 | 6.68007 | 1.20225 | 0.000591366 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2584.98 | 0.0515193 | 779.833ms | 1691 | 4890 | 505.154 | 623.86 | 0.0548879 | 2.12066 | 8.68717 | 1.43998 | 0.000811949 | 4.03919e-05 | 1.66889e-05 | 2(Loss) | true |
