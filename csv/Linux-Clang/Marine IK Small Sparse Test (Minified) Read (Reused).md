
----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4247.02 | 0.0237812 | 820.573ms | 4604 | 4890 | 295.581 | 1033.83 | 0.0539123 | 1.25979 | 6.6477 | 0.923545 | 0.00043476 | 2.44297e-05 | 9.77189e-07 | 1(Win) | true |
| simdjson (ondemand) | 4024.67 | 0.0545372 | 825.275ms | 4604 | 160 | 56.639 | 1090.95 | 0.0721327 | 1.32757 | 6.77476 | 0.940269 | 0.000435762 | 4.07255e-05 | 1.35752e-06 | 2(Loss) | true |
