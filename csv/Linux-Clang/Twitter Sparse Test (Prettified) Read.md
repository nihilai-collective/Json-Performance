
----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7948.44 | 0.0385646 | 5059.97ms | 360584 | 4890 | 1.36125e+06 | 43263.8 | 0.0428151 | 0.637748 | 3.00187 | 0.372818 | 0.000750559 | 1.45583e-06 | 5.66566e-07 | 1(Win) | true |
| simdjson (ondemand) | 7267.6 | 0.0320834 | 5467.98ms | 360584 | 2560 | 589972 | 47316.8 | 0.105969 | 0.695118 | 3.19736 | 0.335857 | 0.000805887 | 2.43095e-06 | 5.95822e-07 | 2(Loss) | true |
