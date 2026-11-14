
----
### Apache Builds Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1846.26 | 0.193085 | 5680.26ms | 94653 | 30 | 267365 | 48892.5 | 0.0271951 | 2.78773 | 12.6873 | 2.50996 | 0.00778 | 3.8738e-06 | 7.04327e-07 | 1(Win) | true |
| simdjson (ondemand) | 1576.39 | 0.0379879 | 6440.24ms | 94653 | 1280 | 605679 | 57262.6 | 0.0955315 | 3.23832 | 13.218 | 2.50911 | 0.00905381 | 2.09565e-05 | 1.36188e-05 | 2(Loss) | true |
