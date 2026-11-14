
----
### Discord Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3092.95 | 0.0456351 | 2745.88ms | 56369 | 4890 | 307640 | 17380.7 | 0.027386 | 1.65713 | 8.13257 | 1.36249 | 0.00279289 | 1.37278e-05 | 6.73331e-06 | 1(Win) | true |
| simdjson (ondemand) | 2659.97 | 0.0170124 | 3031.83ms | 56369 | 4890 | 57805.6 | 20209.9 | 0.0225787 | 1.93435 | 8.60265 | 1.3593 | 0.00302071 | 6.20364e-06 | 1.85384e-06 | 2(Loss) | true |
