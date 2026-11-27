
----
### Canada Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5742.22 | 0.198229 | 9068.35ms | 2090234 | 1280 | 6.0614e+08 | 347148 | 0.221855 | 0.882874 | 4.62825 | 0.756367 | 0.00635327 | 0.0759467 | 3.51075e-06 | 1(Win) | true |
| simdjson (ondemand) | 5428.2 | 0.0488206 | 9686.59ms | 2090234 | 640 | 2.05714e+07 | 367231 | 0.207604 | 0.92784 | 5.10589 | 0.738322 | 0.00287502 | 0.0753171 | 2.96842e-06 | 2(Loss) | true |
