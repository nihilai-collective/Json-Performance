
----
### Twitter Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5717.46 | 0.181112 | 764.748ms | 2821 | 2560 | 1859.24 | 470.544 | 0.114194 | 0.96871 | 3.72847 | 0.511521 | 0.000485616 | 2.97711e-05 | 3.60023e-06 | 1(Win) | true |
| simdjson (ondemand) | 5216.34 | 0.053445 | 770.741ms | 2821 | 4890 | 371.533 | 515.748 | 0.0612734 | 1.05343 | 3.99832 | 0.449859 | 0.00108107 | 2.26899e-05 | 1.88478e-06 | 2(Loss) | true |
