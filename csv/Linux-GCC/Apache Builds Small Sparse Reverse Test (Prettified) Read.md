
----
### Apache Builds Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2849.55 | 0.0460469 | 828.499ms | 3370 | 4890 | 1318.91 | 1127.86 | 0.0179213 | 1.86792 | 7.74807 | 1.39229 | 0.000594625 | 3.84725e-05 | 4.91526e-06 | 1(Win) | true |
| simdjson (ondemand) | 2693.2 | 0.0636207 | 835.538ms | 3370 | 160 | 92.2229 | 1193.33 | 0.14949 | 1.97529 | 7.83976 | 1.35015 | 0.00107567 | 7.4184e-06 | 0 | 2(Loss) | true |
