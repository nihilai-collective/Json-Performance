
----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3998.79 | 0.0413684 | 961.833ms | 9378 | 4890 | 4186.1 | 2236.57 | 0.283771 | 1.30389 | 5.78482 | 0.924398 | 0.00104539 | 1.80992e-05 | 6.10575e-06 | 1(Win) | true |
| simdjson (ondemand) | 3756.26 | 0.0442489 | 957.263ms | 9378 | 160 | 177.597 | 2380.97 | 0.000524992 | 1.39448 | 6.12487 | 0.932821 | 0.00106633 | 1.99936e-05 | 1.33291e-06 | 2(Loss) | true |
