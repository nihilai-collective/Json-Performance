
----
### Random Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1904.72 | 0.0319554 | 965.565ms | 4926 | 4890 | 3037.57 | 2466.41 | 0.126564 | 2.74542 | 12.3382 | 2.2905 | 0.00349396 | 4.29672e-05 | 1.43224e-05 | 1(Win) | true |
| simdjson (ondemand) | 1476.67 | 0.0593715 | 1037.29ms | 4926 | 1280 | 4566.53 | 3181.34 | 0.255527 | 3.53007 | 13.9982 | 2.49574 | 0.00661477 | 5.58262e-05 | 2.77545e-05 | 2(Loss) | true |
