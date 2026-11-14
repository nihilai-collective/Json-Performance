
----
### Marine IK Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4744.56 | 0.0826638 | 9613.94ms | 1834197 | 640 | 5.94443e+07 | 368680 | 0.0350252 | 1.07203 | 6.28014 | 0.838105 | 0.0021911 | 0.0755262 | 5.57465e-06 | 1(Win) | true |
| simdjson (ondemand) | 4394.17 | 0.0804067 | 5182.74ms | 1834197 | 80 | 8.19622e+06 | 398079 | 0.0350776 | 1.16933 | 6.33083 | 0.867833 | 0.00330446 | 0.0754515 | 8.85946e-07 | 2(Loss) | true |
