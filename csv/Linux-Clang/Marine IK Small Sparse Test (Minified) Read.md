
----
### Marine IK Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4143.18 | 0.0310621 | 821.624ms | 4604 | 4890 | 529.874 | 1059.75 | 0.0435961 | 1.29061 | 6.73501 | 0.943093 | 0.000434583 | 2.18979e-05 | 7.10683e-07 | 1(Win) | true |
| simdjson (ondemand) | 3918.72 | 0.0279577 | 826.152ms | 4604 | 1280 | 125.602 | 1120.45 | 0.019876 | 1.36264 | 6.86208 | 0.959818 | 0.000438138 | 2.2399e-05 | 5.93913e-06 | 2(Loss) | true |
