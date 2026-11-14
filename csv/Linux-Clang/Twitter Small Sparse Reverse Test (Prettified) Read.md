
----
### Twitter Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5161.66 | 0.129137 | 782.843ms | 3770 | 160 | 129.457 | 696.55 | 0.0754283 | 1.05896 | 4.55438 | 0.680902 | 0.000734416 | 2.15517e-05 | 6.6313e-06 | 1(Win) | true |
| simdjson (ondemand) | 4730.72 | 0.0353832 | 788.634ms | 3770 | 4890 | 353.615 | 760.002 | 0.136503 | 1.14468 | 5.01698 | 0.691777 | 0.000721442 | 2.99968e-05 | 6.34652e-06 | 2(Loss) | true |
