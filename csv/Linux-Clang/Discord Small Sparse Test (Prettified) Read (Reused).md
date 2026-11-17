
----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5622.84 | 0.0435679 | 836.579ms | 6701 | 2560 | 627.685 | 1136.54 | 0.0932611 | 0.948548 | 4.08626 | 0.576034 | 0.000738929 | 2.40752e-05 | 6.58717e-06 | 1(Win) | true |
| simdjson (ondemand) | 5238.82 | 0.0453425 | 844.251ms | 6701 | 4890 | 1496 | 1219.85 | 0.0592802 | 1.01519 | 4.33637 | 0.530369 | 0.000294068 | 1.20545e-05 | 1.86158e-06 | 2(Loss) | true |
