
----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1704.36 | 0.0330244 | 966.57ms | 4390 | 4890 | 3217.99 | 2456.42 | 0.00259248 | 3.06515 | 14.0765 | 2.64374 | 0.00437726 | 3.20025e-05 | 3.77322e-06 | 1(Win) | true |
| simdjson (ondemand) | 1581.7 | 0.0929591 | 985.082ms | 4390 | 40 | 242.174 | 2646.93 | 0.0185785 | 3.30764 | 14.6797 | 2.42187 | 0.00299544 | 0 | 0 | 2(Loss) | true |
