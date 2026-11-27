
----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4509.58 | 0.04659 | 3878.34ms | 124597 | 640 | 96451.2 | 26349.4 | 0.212644 | 1.12768 | 5.77635 | 0.935493 | 0.00170081 | 5.65573e-06 | 3.72451e-06 | 1(Win) | true |
| simdjson (ondemand) | 3043 | 0.0336876 | 5137.74ms | 124597 | 1280 | 221493 | 39048.6 | 0.0309706 | 1.6755 | 6.77486 | 1.13259 | 0.00499159 | 1.0233e-05 | 7.00383e-06 | 2(Loss) | true |
