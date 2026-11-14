
----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8553.02 | 0.0688507 | 6152.82ms | 2090234 | 640 | 1.64796e+07 | 233064 | 0.06901 | 0.591451 | 3.18965 | 0.396912 | 0.00243292 | 0.0508256 | 1.6767e-06 | 1(Win) | true |
| simdjson (ondemand) | 7411.15 | 0.0550718 | 7075.27ms | 2090234 | 320 | 7.02145e+06 | 268973 | 0.149928 | 0.689356 | 3.66628 | 0.418404 | 0.00236034 | 0.0493786 | 2.77481e-06 | 2(Loss) | true |
