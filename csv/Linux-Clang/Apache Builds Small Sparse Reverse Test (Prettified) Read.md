
----
### Apache Builds Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2904.12 | 0.0825949 | 835.399ms | 3370 | 2560 | 2138.83 | 1106.66 | 0.00183544 | 1.81681 | 7.58279 | 1.38902 | 0.00121105 | 3.33828e-05 | 8.46161e-06 | 1(Win) | true |
| simdjson (ondemand) | 2592.39 | 0.0361685 | 847.765ms | 3370 | 1280 | 257.353 | 1239.74 | 0.153683 | 2.05148 | 7.98071 | 1.31365 | 0.00321796 | 1.3214e-05 | 3.01372e-06 | 2(Loss) | true |
