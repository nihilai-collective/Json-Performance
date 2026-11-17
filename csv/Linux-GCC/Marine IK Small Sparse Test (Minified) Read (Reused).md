
----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4153.45 | 0.0976363 | 824.12ms | 4604 | 80 | 85.2247 | 1057.12 | 0.0661735 | 1.28671 | 6.17029 | 0.907472 | 0.000434405 | 1.08601e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3904.67 | 0.0615653 | 829.098ms | 4604 | 2560 | 1226.92 | 1124.48 | 0.0371909 | 1.36563 | 6.96785 | 0.957863 | 0.000442889 | 2.12112e-05 | 3.2241e-06 | 2(Loss) | true |
