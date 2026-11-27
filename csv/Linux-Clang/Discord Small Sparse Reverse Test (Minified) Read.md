
----
### Discord Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3050.44 | 0.171349 | 870.379ms | 4857 | 1280 | 8665.3 | 1518.47 | 0.0514748 | 1.73044 | 7.25633 | 1.28804 | 0.00188066 | 5.30806e-05 | 2.17148e-05 | 1(Win) | true |
| simdjson (ondemand) | 2118.7 | 0.183646 | 940.887ms | 4857 | 160 | 2579.17 | 2186.24 | 0.211137 | 2.47669 | 10.666 | 1.65061 | 0.00222231 | 5.79061e-05 | 3.86041e-05 | 2(Loss) | true |
