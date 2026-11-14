
----
### Twitter Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4704.54 | 0.067937 | 6043.04ms | 264040 | 640 | 846248 | 53524.5 | 0.0277287 | 1.07642 | 5.32372 | 0.874159 | 0.00217223 | 1.24271e-06 | 2.89966e-07 | 1(Win) | true |
| simdjson (ondemand) | 4028.32 | 0.0949845 | 7030.88ms | 264040 | 160 | 564050 | 62509.5 | 0.00600945 | 1.26523 | 6.33596 | 0.950828 | 0.00212184 | 1.3729e-06 | 3.31389e-07 | 2(Loss) | true |
