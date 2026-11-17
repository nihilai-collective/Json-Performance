
----
### CitmCatalog Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5443.84 | 0.052315 | 9523.73ms | 500299 | 640 | 1.34549e+06 | 87644.5 | 0.0828872 | 0.938007 | 4.98824 | 0.721071 | 0.000931733 | 1.83984e-05 | 3.08878e-06 | 1(Win) | true |
| simdjson (ondemand) | 4984.87 | 0.0297389 | 5273.86ms | 500299 | 1280 | 1.03708e+06 | 95714.1 | 0.0610278 | 1.02656 | 5.64575 | 0.723983 | 0.00102418 | 0.000606551 | 1.73818e-05 | 2(Loss) | true |
