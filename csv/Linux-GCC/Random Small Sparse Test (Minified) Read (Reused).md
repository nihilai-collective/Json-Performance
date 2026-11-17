
----
### Random Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2749.56 | 0.113678 | 909.58ms | 4926 | 640 | 2414.33 | 1708.57 | 0.0274278 | 1.91523 | 8.76492 | 1.46691 | 0.00177788 | 1.52253e-05 | 2.22036e-06 | 1(Win) | true |
| simdjson (ondemand) | 2256.44 | 0.0368065 | 934.959ms | 4926 | 2560 | 1503.25 | 2081.95 | 0.0957467 | 2.32678 | 9.42408 | 1.50467 | 0.00246175 | 2.00626e-05 | 1.58597e-06 | 2(Loss) | true |
