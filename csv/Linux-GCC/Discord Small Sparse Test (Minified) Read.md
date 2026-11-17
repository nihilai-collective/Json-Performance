
----
### Discord Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4056.78 | 0.122935 | 830.334ms | 4857 | 640 | 1260.97 | 1141.79 | 0.0506588 | 1.3136 | 5.51799 | 0.850808 | 0.000211679 | 2.09105e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3717.33 | 0.0608939 | 840.68ms | 4857 | 320 | 184.235 | 1246.06 | 0.00601935 | 1.43115 | 5.98044 | 0.837142 | 0.000231624 | 3.53871e-05 | 0 | 2(Loss) | true |
