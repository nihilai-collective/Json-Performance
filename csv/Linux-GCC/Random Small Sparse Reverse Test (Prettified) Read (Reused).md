
----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3287.43 | 0.0622489 | 964.965ms | 8150 | 1280 | 2772.52 | 2364.29 | 0.124816 | 1.5732 | 7.17546 | 1.26994 | 0.00233762 | 7.95629e-06 | 9.58589e-08 | 1(Win) | true |
| simdjson (ondemand) | 2559.15 | 0.0923656 | 1041.7ms | 8150 | 40 | 314.779 | 3037.12 | 0.0551204 | 2.07668 | 8.5746 | 1.42883 | 0.00421472 | 1.53374e-05 | 9.20245e-06 | 2(Loss) | true |
