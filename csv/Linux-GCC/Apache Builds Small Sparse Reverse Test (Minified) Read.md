
----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2559.45 | 0.0921411 | 815.219ms | 2632 | 1280 | 1045.19 | 980.706 | 0.219067 | 2.07873 | 8.88754 | 1.65958 | 0.00076344 | 3.2651e-05 | 1.12794e-05 | 1(Win) | true |
| simdjson (ondemand) | 2067.43 | 0.0598649 | 837.584ms | 2632 | 4890 | 2583.24 | 1214.1 | 0.177721 | 2.57717 | 9.8845 | 1.76558 | 0.00207296 | 8.13489e-05 | 5.07363e-05 | 2(Loss) | true |
