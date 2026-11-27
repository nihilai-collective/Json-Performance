
----
### Marine IK Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3061.35 | 0.0878068 | 7358.38ms | 1834197 | 640 | 1.61102e+08 | 571390 | 0.110867 | 1.65817 | 8.47945 | 1.62435 | 0.00610163 | 0.113216 | 2.45083e-06 | 1(Win) | true |
| simdjson (ondemand) | 2443.78 | 0.175821 | 9178.09ms | 1834197 | 80 | 1.26706e+08 | 715786 | 0.157919 | 2.06826 | 12.6838 | 2.27012 | 0.00344015 | 0.150495 | 7.27839e-06 | 2(Loss) | true |
