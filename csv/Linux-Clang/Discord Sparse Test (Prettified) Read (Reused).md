
----
### Discord Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3953 | 0.0499691 | 3070.62ms | 83958 | 1280 | 131124 | 20255.2 | 0.100287 | 1.29628 | 6.08529 | 0.97469 | 0.00167287 | 1.70565e-05 | 1.11198e-05 | 1(Win) | true |
| simdjson (ondemand) | 3752.91 | 0.0823952 | 3135.59ms | 83958 | 320 | 98887.3 | 21335 | 0.114761 | 1.35301 | 6.33461 | 0.926817 | 0.00180604 | 1.00497e-05 | 7.25809e-06 | 2(Loss) | true |
