
----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1816.93 | 0.0311975 | 1341.03ms | 11812 | 4890 | 18294.4 | 6199.91 | 0.0551728 | 2.85018 | 13.6985 | 2.58999 | 0.00688181 | 4.25895e-05 | 1.85593e-05 | 1(Win) | true |
| simdjson (ondemand) | 1630.53 | 0.0511826 | 1408.84ms | 11812 | 2560 | 32009.2 | 6908.68 | 0.00203552 | 3.17514 | 14.0097 | 2.44311 | 0.0077879 | 1.54438e-05 | 1.12439e-06 | 2(Loss) | true |
