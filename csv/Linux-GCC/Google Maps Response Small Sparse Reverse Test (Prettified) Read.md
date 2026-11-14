
----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3255.03 | 0.0854606 | 997.572ms | 9378 | 640 | 3528.76 | 2747.61 | 0.0729079 | 1.60372 | 7.25432 | 1.27714 | 0.0022851 | 1.11631e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3111.49 | 0.0429643 | 1002.37ms | 9378 | 2560 | 3904.25 | 2874.36 | 0.050621 | 1.67658 | 7.28642 | 1.17115 | 0.00231234 | 1.05799e-05 | 9.16373e-07 | 2(Loss) | true |
