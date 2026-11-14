
----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3321.9 | 0.13145 | 1009.27ms | 9378 | 1280 | 16031.7 | 2692.3 | 0.293898 | 1.57078 | 7.11804 | 1.24462 | 0.00230018 | 1.77443e-05 | 6.66453e-07 | 1(Win) | true |
| simdjson (ondemand) | 3150.51 | 0.23992 | 1044.14ms | 9378 | 640 | 29687.6 | 2838.77 | 0.274971 | 1.65921 | 7.14598 | 1.13777 | 0.00328661 | 1.33291e-05 | 3.33227e-07 | 2(Loss) | true |
