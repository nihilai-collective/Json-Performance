
----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3289.89 | 0.124945 | 999.186ms | 9378 | 40 | 461.487 | 2718.5 | 0.111706 | 1.62042 | 7.39678 | 1.14758 | 0.00171945 | 2.13265e-05 | 2.66581e-06 | 1(Win) | true |
| Jsonifier (generic) | 3164.81 | 0.112647 | 994.374ms | 9378 | 80 | 810.692 | 2825.94 | 0.367109 | 1.6513 | 7.27138 | 1.28983 | 0.0018754 | 2.39923e-05 | 1.59949e-05 | 2(Loss) | true |
