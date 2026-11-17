
----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10385.1 | 0.0810497 | 885.779ms | 18245 | 640 | 1180.19 | 1675.46 | 0.00615464 | 0.5075 | 2.51987 | 0.269499 | 0.000164942 | 5.73787e-06 | 2.5692e-07 | 1(Win) | true |
| simdjson (ondemand) | 10059.1 | 0.0477238 | 894.1ms | 18245 | 2560 | 1744.53 | 1729.75 | 0.0156523 | 0.523675 | 2.63913 | 0.278488 | 0.000177232 | 6.55145e-06 | 1.19896e-06 | 2(Loss) | true |
