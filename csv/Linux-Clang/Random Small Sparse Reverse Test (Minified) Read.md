
----
### Random Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1901.7 | 0.111452 | 963.606ms | 4926 | 1280 | 9702.61 | 2470.32 | 0.00449102 | 2.7516 | 12.0481 | 2.29781 | 0.00321524 | 0.000112128 | 3.91735e-05 | 1(Win) | true |
| simdjson (ondemand) | 1575.58 | 0.0389518 | 1014.1ms | 4926 | 4890 | 6595.86 | 2981.63 | 0.00985609 | 3.31083 | 14.6072 | 2.446 | 0.00449138 | 2.38707e-05 | 1.20391e-06 | 2(Loss) | true |
