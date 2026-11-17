
----
### Random Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2944.65 | 0.0377828 | 992.611ms | 8150 | 2560 | 2546.1 | 2639.51 | 0.125372 | 1.77283 | 7.76859 | 1.34871 | 0.00251198 | 1.00652e-05 | 2.06097e-06 | 1(Win) | true |
| simdjson (ondemand) | 2474.32 | 0.0626931 | 1044.65ms | 8150 | 80 | 310.266 | 3141.25 | 0.131939 | 2.1124 | 8.58049 | 1.43117 | 0.00457822 | 1.99387e-05 | 4.60123e-06 | 2(Loss) | true |
