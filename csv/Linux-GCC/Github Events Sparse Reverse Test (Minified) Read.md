
----
### Github Events Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5668.92 | 0.118384 | 1622.9ms | 53331 | 640 | 72197.7 | 8971.8 | 0.0939215 | 0.905293 | 4.33193 | 0.701806 | 0.00176565 | 3.1056e-06 | 1.17193e-07 | 1(Win) | true |
| simdjson (ondemand) | 4232.82 | 0.0288343 | 1926.82ms | 53331 | 4890 | 58698.6 | 12015.7 | 0.0626241 | 1.21728 | 5.84767 | 0.954323 | 0.00238064 | 7.22808e-06 | 3.17499e-06 | 2(Loss) | true |
