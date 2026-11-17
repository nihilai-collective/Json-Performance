
----
### Random Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2771.4 | 0.051064 | 898.266ms | 4926 | 320 | 239.755 | 1695.1 | 0.165461 | 1.90586 | 8.32318 | 1.51786 | 0.0027044 | 4.37728e-05 | 6.34389e-07 | 1(Win) | true |
| simdjson (ondemand) | 2372.79 | 0.0303246 | 926.313ms | 4926 | 640 | 230.698 | 1979.87 | 0.0401539 | 2.21551 | 9.68473 | 1.48112 | 0.00155425 | 2.09348e-05 | 6.34389e-07 | 2(Loss) | true |
