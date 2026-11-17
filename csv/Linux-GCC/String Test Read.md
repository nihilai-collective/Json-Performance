
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1381.55 | 0.250252 | 1371.13ms | 9578 | 80 | 21901 | 6611.64 | 0.028178 | 3.7454 | 17.7196 | 3.34172 | 0.00182188 | 3.13218e-05 | 1.30507e-06 | 1(Win) | true |
| simdjson (ondemand) | 1348.36 | 0.763663 | 1399.8ms | 9578 | 4890 | 1.30874e+07 | 6774.39 | 0.0929145 | 3.77733 | 19.237 | 2.98089 | 0.00333969 | 3.09802e-05 | 8.92468e-06 | 2(Loss) | true |
