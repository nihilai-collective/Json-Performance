
----
### Instruments Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4730.39 | 0.0526969 | 815.987ms | 4669 | 320 | 78.736 | 941.297 | 0.120367 | 1.13738 | 5.11501 | 0.768473 | 0.00086073 | 1.60634e-05 | 6.69308e-07 | 1(Win) | true |
| simdjson (ondemand) | 4184.92 | 0.163769 | 826.74ms | 4669 | 80 | 242.899 | 1063.99 | 0.0293793 | 1.27833 | 5.62947 | 0.697794 | 0.00144035 | 1.33862e-05 | 2.67723e-06 | 2(Loss) | true |
