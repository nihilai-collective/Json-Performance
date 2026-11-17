
----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2951.21 | 0.0578878 | 3734.91ms | 83958 | 1280 | 315725 | 27130.8 | 0.0367078 | 1.73703 | 8.30289 | 1.48379 | 0.00284099 | 4.45721e-06 | 1.0701e-06 | 1(Win) | true |
| simdjson (ondemand) | 2145.65 | 0.0683258 | 4759.99ms | 83958 | 640 | 416062 | 37316.8 | 0.0385653 | 2.39594 | 10.4968 | 1.7775 | 0.0077565 | 3.57322e-06 | 8.74693e-07 | 2(Loss) | true |
