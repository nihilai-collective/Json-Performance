
----
### Apache Builds Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2759.66 | 0.0658361 | 808.786ms | 2632 | 4890 | 1753.47 | 909.557 | 0.0310362 | 1.94718 | 8.30595 | 1.49584 | 0.00114596 | 1.68603e-05 | 2.17552e-06 | 1(Win) | true |
| simdjson (ondemand) | 2384.41 | 0.106185 | 821.91ms | 2632 | 80 | 99.9595 | 1052.7 | 0.0593359 | 2.24413 | 8.84384 | 1.51406 | 0.00166223 | 0 | 0 | 2(Loss) | true |
