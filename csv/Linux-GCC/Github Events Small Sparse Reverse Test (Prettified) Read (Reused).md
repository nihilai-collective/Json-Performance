
----
### Github Events Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3979.17 | 0.0402848 | 766.555ms | 2158 | 1280 | 55.5659 | 517.2 | 0.000906314 | 1.3925 | 5.29286 | 0.891566 | 0.00124211 | 3.54785e-05 | 7.60253e-06 | 1(Win) | true |
| simdjson (ondemand) | 3291.86 | 0.0380682 | 779.479ms | 2158 | 1280 | 72.5027 | 625.188 | 0.0122478 | 1.66582 | 6.65616 | 1.08804 | 0.000846777 | 2.28076e-05 | 3.62025e-07 | 2(Loss) | true |
