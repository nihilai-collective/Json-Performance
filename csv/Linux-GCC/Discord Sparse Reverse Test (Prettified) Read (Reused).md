
----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2938.11 | 0.0194723 | 3745.4ms | 83958 | 4890 | 137699 | 27251.7 | 0.0271067 | 1.7452 | 8.33257 | 1.48975 | 0.00258113 | 4.39406e-06 | 1.07659e-06 | 1(Win) | true |
| simdjson (ondemand) | 2169.68 | 0.0328296 | 4691.6ms | 83958 | 2560 | 375754 | 36903.4 | 0.0920065 | 2.35645 | 10.4896 | 1.77323 | 0.00641597 | 6.40201e-06 | 2.43797e-06 | 2(Loss) | true |
