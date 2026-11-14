
----
### CitmCatalog Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5593.05 | 0.141429 | 5154.27ms | 1151920 | 1280 | 9.87719e+07 | 196415 | 0.128611 | 0.901629 | 4.82313 | 0.792329 | 0.00112346 | 0.00482896 | 1.93664e-05 | 1(Win) | true |
| simdjson (ondemand) | 5559.5 | 0.0773919 | 5218ms | 1151920 | 160 | 3.74183e+06 | 197600 | 0.186973 | 0.91454 | 5.18976 | 0.785102 | 0.00144542 | 0.00513046 | 6.51087e-06 | 2(Loss) | true |
