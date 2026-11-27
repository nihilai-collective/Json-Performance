
----
### Discord Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4397.23 | 0.21644 | 2849.42ms | 83958 | 320 | 497041 | 18208.9 | 0.05756 | 1.15409 | 5.84552 | 0.934324 | 0.00184512 | 1.46278e-05 | 9.97523e-06 | 1(Win) | true |
| simdjson (ondemand) | 3622.23 | 0.0423656 | 3218.73ms | 83958 | 640 | 56128 | 22104.8 | 0.0681231 | 1.40075 | 6.20491 | 0.926011 | 0.00213302 | 1.33809e-05 | 8.82137e-06 | 2(Loss) | true |
