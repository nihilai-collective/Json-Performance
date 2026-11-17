
----
### Random Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2510.44 | 0.0331975 | 904.937ms | 4926 | 4890 | 1887.17 | 1871.31 | 0.0213588 | 2.09494 | 8.92814 | 1.66565 | 0.00237764 | 4.47108e-05 | 8.59344e-06 | 1(Win) | true |
| simdjson (ondemand) | 2178.11 | 0.0273887 | 933.788ms | 4926 | 4890 | 1706.41 | 2156.83 | 0.146374 | 2.40819 | 10.2887 | 1.62789 | 0.00156463 | 2.23346e-05 | 3.03054e-06 | 2(Loss) | true |
