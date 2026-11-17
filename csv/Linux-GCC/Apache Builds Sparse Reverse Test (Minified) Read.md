
----
### Apache Builds Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1820.82 | 0.0902405 | 5711.66ms | 94653 | 1280 | 2.5618e+06 | 49575.4 | 0.0137499 | 2.7678 | 12.6873 | 2.50996 | 0.00767166 | 1.07547e-05 | 6.92497e-06 | 1(Win) | true |
| simdjson (ondemand) | 1539 | 0.0336766 | 6576.46ms | 94653 | 1280 | 499411 | 58653.7 | 0.068052 | 3.2851 | 13.2163 | 2.50824 | 0.00952562 | 8.46843e-06 | 3.13646e-06 | 2(Loss) | true |
