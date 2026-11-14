
----
### Apache Builds Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3188.58 | 0.167086 | 790.606ms | 2632 | 160 | 276.806 | 787.206 | 0.0627612 | 1.69835 | 6.87462 | 1.23708 | 0.000660144 | 2.37462e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2401.52 | 0.0536208 | 817.061ms | 2632 | 4890 | 1535.94 | 1045.2 | 0.216269 | 2.22937 | 8.21999 | 1.34385 | 0.00319203 | 5.01924e-05 | 5.28341e-06 | 2(Loss) | true |
