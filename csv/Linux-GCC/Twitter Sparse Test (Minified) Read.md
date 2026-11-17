
----
### Twitter Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6945.36 | 0.109636 | 4407.53ms | 264040 | 80 | 126399 | 36255.6 | 0.10119 | 0.741847 | 3.61395 | 0.467861 | 0.00136409 | 3.35176e-05 | 2.79787e-05 | 1(Win) | true |
| simdjson (ondemand) | 6201.05 | 0.0321218 | 4783.18ms | 264040 | 4890 | 831992 | 40607.3 | 0.299706 | 0.814996 | 4.00273 | 0.440913 | 0.00109387 | 1.30224e-05 | 9.43651e-06 | 2(Loss) | true |
