
----
### Apache Builds Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2503.8 | 0.105986 | 4378.24ms | 94653 | 640 | 934429 | 36052.4 | 0.190567 | 2.02532 | 9.5773 | 1.71248 | 0.00517287 | 3.89581e-06 | 1.43617e-06 | 1(Win) | true |
| simdjson (ondemand) | 1794.02 | 0.0190647 | 5780.26ms | 94653 | 4890 | 449969 | 50316.1 | 0.00156859 | 2.84297 | 10.6669 | 1.97229 | 0.00829069 | 2.38996e-05 | 1.69557e-05 | 2(Loss) | true |
