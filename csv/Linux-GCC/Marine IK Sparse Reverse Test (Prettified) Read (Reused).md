
----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7647.8 | 0.180826 | 5792.32ms | 7351818 | 160 | 4.39701e+08 | 916766 | 0.219158 | 0.662896 | 2.9452 | 0.432012 | 0.00202635 | 0.0635494 | 1.15065e-05 | 1(Win) | true |
| simdjson (ondemand) | 6073.05 | 0.340826 | 7325.67ms | 7351818 | 80 | 1.2386e+09 | 1.15448e+06 | 0.198339 | 0.838115 | 4.22108 | 0.6065 | 0.00105698 | 0.0847711 | 1.32518e-05 | 2(Loss) | true |
