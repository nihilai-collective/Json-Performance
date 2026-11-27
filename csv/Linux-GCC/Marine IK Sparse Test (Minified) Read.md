
----
### Marine IK Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4467.38 | 0.132867 | 5083.36ms | 1834197 | 320 | 8.66106e+07 | 391555 | 0.0832171 | 1.13744 | 5.76948 | 0.914934 | 0.00579317 | 0.0755215 | 1.1335e-05 | 1(Win) | true |
| simdjson (ondemand) | 4350.73 | 0.107326 | 5216.29ms | 1834197 | 320 | 5.95843e+07 | 402054 | 0.0553359 | 1.16838 | 6.52918 | 0.874486 | 0.00334902 | 0.075429 | 7.61062e-06 | 2(Loss) | true |
