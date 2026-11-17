
----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4200.29 | 0.0525806 | 822.121ms | 4604 | 1280 | 386.699 | 1045.34 | 0.0243582 | 1.27156 | 6.64705 | 0.923545 | 0.000651438 | 1.88355e-05 | 1.69689e-07 | 1(Win) | true |
| simdjson (ondemand) | 3984.39 | 0.0647521 | 826.675ms | 4604 | 4890 | 2489.8 | 1101.98 | 0.0712855 | 1.33736 | 6.78193 | 0.942876 | 0.00045768 | 2.47406e-05 | 4.61944e-06 | 2(Loss) | true |
