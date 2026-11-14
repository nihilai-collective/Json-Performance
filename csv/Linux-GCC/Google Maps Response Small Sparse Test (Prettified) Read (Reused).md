
----
### Google Maps Response Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4232.61 | 0.0732942 | 948.315ms | 9378 | 1280 | 3070.1 | 2113.01 | 0.0543063 | 1.23853 | 5.64865 | 0.891875 | 0.00104458 | 1.39122e-05 | 2.58251e-06 | 1(Win) | true |
| simdjson (ondemand) | 3763.49 | 0.0582329 | 956.937ms | 9378 | 160 | 306.405 | 2376.4 | 0.0110473 | 1.39135 | 5.95991 | 0.894647 | 0.00141221 | 1.86607e-05 | 6.66453e-07 | 2(Loss) | true |
