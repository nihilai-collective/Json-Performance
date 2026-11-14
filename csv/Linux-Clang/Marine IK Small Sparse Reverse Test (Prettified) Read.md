
----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7452.97 | 0.0362742 | 951.994ms | 18245 | 2560 | 1835.97 | 2334.61 | 0.0574913 | 0.703022 | 3.30863 | 0.461113 | 0.000274776 | 6.53004e-06 | 3.4256e-07 | 1(Win) | true |
| simdjson (ondemand) | 6275.69 | 0.0279998 | 995.882ms | 18245 | 1280 | 771.407 | 2772.57 | 0.000394488 | 0.833096 | 4.27569 | 0.634037 | 0.000330913 | 5.65223e-06 | 8.56399e-08 | 2(Loss) | true |
