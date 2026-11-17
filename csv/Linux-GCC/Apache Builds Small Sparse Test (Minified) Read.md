
----
### Apache Builds Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3221.72 | 0.139822 | 799.434ms | 2632 | 1280 | 1519 | 779.108 | 0.0467063 | 1.66249 | 7.05775 | 1.16641 | 0.000387657 | 1.51382e-05 | 1.48414e-06 | 1(Win) | true |
| simdjson (ondemand) | 2326.23 | 0.0797993 | 824.11ms | 2632 | 2560 | 1898.03 | 1079.03 | 0.091217 | 2.29356 | 8.1079 | 1.38754 | 0.00102079 | 3.04248e-05 | 4.00717e-06 | 2(Loss) | true |
