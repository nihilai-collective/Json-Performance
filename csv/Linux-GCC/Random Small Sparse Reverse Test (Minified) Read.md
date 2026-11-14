
----
### Random Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1878.71 | 0.035222 | 966.493ms | 4926 | 4890 | 3793.2 | 2500.54 | 0.00255613 | 2.78402 | 12.3382 | 2.2905 | 0.00307018 | 2.76069e-05 | 6.68379e-06 | 1(Win) | true |
| simdjson (ondemand) | 1448.32 | 0.0291399 | 1041.23ms | 4926 | 4890 | 4368.62 | 3243.62 | 0.0138523 | 3.59656 | 13.9832 | 2.49006 | 0.00725291 | 2.43273e-05 | 3.27962e-06 | 2(Loss) | true |
