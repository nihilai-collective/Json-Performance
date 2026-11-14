
----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5020.04 | 0.0487657 | 9110.92ms | 1834197 | 320 | 9.23968e+06 | 348448 | 0.176806 | 1.02136 | 5.69871 | 0.827937 | 0.000710691 | 0.0755821 | 1.63048e-06 | 1(Win) | true |
| simdjson (ondemand) | 4289.98 | 0.0742648 | 5276.16ms | 1834197 | 160 | 1.46712e+07 | 407747 | 0.219137 | 1.1847 | 6.52899 | 0.874438 | 0.00494396 | 0.0754424 | 3.30526e-06 | 2(Loss) | true |
