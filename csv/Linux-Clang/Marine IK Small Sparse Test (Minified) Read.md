
----
### Marine IK Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4086.62 | 0.157569 | 823.381ms | 4604 | 640 | 1834.27 | 1074.41 | 0.00552658 | 1.30452 | 6.73436 | 0.943093 | 0.000651947 | 1.32358e-05 | 3.39379e-07 | 1(Win) | true |
| simdjson (ondemand) | 3915.54 | 0.0572536 | 828.326ms | 4604 | 2560 | 1055.2 | 1121.36 | 0.0152949 | 1.36056 | 6.86924 | 0.962424 | 0.000452137 | 1.86658e-05 | 2.88472e-06 | 2(Loss) | true |
