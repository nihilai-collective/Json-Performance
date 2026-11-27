
----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5788.8 | 0.211374 | 5071.86ms | 1151920 | 640 | 1.02979e+08 | 189773 | 0.339852 | 0.881606 | 4.79747 | 0.812939 | 0.00122002 | 0.00405208 | 6.40235e-06 | 1(Win) | true |
| simdjson (ondemand) | 5369.6 | 0.113295 | 5487.43ms | 1151920 | 80 | 4.29807e+06 | 204588 | 0.219917 | 0.947407 | 5.18929 | 0.785758 | 0.00162849 | 0.0117797 | 5.6102e-06 | 2(Loss) | true |
