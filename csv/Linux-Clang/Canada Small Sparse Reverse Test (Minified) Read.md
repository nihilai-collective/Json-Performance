
----
### Canada Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5386.73 | 0.0786317 | 795.67ms | 4630 | 4890 | 2031.5 | 819.702 | 0.358844 | 1.00203 | 5.15276 | 0.805195 | 0.000649052 | 1.49289e-05 | 1.01587e-06 | 1(Win) | true |
| simdjson (ondemand) | 5121.66 | 0.085585 | 797.443ms | 4630 | 80 | 43.5538 | 862.125 | 0 | 1.07105 | 5.58445 | 0.817495 | 0.000647948 | 5.39957e-06 | 0 | 2(Loss) | true |
