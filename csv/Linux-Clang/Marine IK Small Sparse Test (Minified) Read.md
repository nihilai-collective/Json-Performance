
----
### Marine IK Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3825.48 | 0.171699 | 836.842ms | 4604 | 2560 | 9942.03 | 1147.76 | 1.06053 | 1.39082 | 6.51151 | 1.01434 | 0.000667388 | 2.52837e-05 | 9.58745e-06 | 1(Win) | true |
| simdjson (ondemand) | 3794.61 | 0.0771214 | 836.718ms | 4604 | 4890 | 3893.99 | 1157.09 | 0.0199239 | 1.40326 | 6.91464 | 0.961121 | 0.000697358 | 2.00768e-05 | 5.55221e-06 | 2(Loss) | true |
