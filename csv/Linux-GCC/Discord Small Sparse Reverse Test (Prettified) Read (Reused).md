
----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4395.09 | 0.132279 | 873.635ms | 6701 | 40 | 147.974 | 1454.03 | 0.119639 | 1.20464 | 5.32413 | 0.867482 | 0.00107074 | 7.46157e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3129.78 | 0.0501384 | 931.572ms | 6701 | 4890 | 5125.11 | 2041.86 | 0.00410189 | 1.66676 | 7.37338 | 1.14863 | 0.00214432 | 2.70387e-05 | 1.19629e-05 | 2(Loss) | true |
