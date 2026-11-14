
----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20977.3 | 0.167849 | 8881.44ms | 7351818 | 30 | 9.44169e+06 | 334229 | 0.578145 | 0.118011 | 1(Win) | true |
| simdjson (stage-1) | 16823.2 | 0.0888493 | 5303.59ms | 7351818 | 320 | 4.38764e+07 | 416760 | 0.0116188 | 0.147155 | 2(Loss) | true |
