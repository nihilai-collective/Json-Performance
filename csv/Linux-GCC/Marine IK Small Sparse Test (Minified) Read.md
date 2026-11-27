
----
### Marine IK Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4276.45 | 0.0484715 | 821.088ms | 4604 | 4890 | 1211.12 | 1026.72 | 0.0352129 | 1.24436 | 6.21986 | 0.990019 | 0.000435116 | 2.28307e-05 | 8.75028e-06 | 1(Win) | true |
| simdjson (ondemand) | 3802.36 | 0.142082 | 835.605ms | 4604 | 30 | 80.754 | 1154.73 | 0.176397 | 1.404 | 7.04974 | 0.978931 | 0.000448885 | 6.51607e-05 | 3.62004e-05 | 2(Loss) | true |
