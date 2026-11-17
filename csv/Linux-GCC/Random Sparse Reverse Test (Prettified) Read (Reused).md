
----
### Random Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2928.86 | 0.0477732 | 6295.78ms | 676745 | 1280 | 1.41851e+07 | 220357 | 0.0076501 | 1.74564 | 7.98831 | 1.39546 | 0.00481469 | 0.000466011 | 7.95513e-06 | 1(Win) | true |
| simdjson (ondemand) | 2401.52 | 0.047742 | 7505.86ms | 676745 | 640 | 1.05356e+07 | 268745 | 0.0773206 | 2.11077 | 8.8494 | 1.49368 | 0.00791351 | 0.00100138 | 5.02636e-06 | 2(Loss) | true |
