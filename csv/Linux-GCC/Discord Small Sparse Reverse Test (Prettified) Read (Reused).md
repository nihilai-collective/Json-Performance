
----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4068.53 | 0.043045 | 879.282ms | 6701 | 2560 | 1170.28 | 1570.73 | 0.120841 | 1.29798 | 5.5726 | 0.913147 | 0.000815643 | 1.79544e-05 | 1.8071e-06 | 1(Win) | true |
| simdjson (ondemand) | 3157.98 | 0.0389836 | 921.296ms | 6701 | 2560 | 1593.18 | 2023.62 | 0.0603441 | 1.66299 | 7.37457 | 1.14923 | 0.00223462 | 1.06094e-05 | 7.57816e-07 | 2(Loss) | true |
