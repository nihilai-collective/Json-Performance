
----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5371.42 | 0.023312 | 9685.45ms | 500299 | 640 | 274424 | 88826.2 | 0.0113868 | 0.958592 | 5.37987 | 0.732364 | 0.00089612 | 3.31364e-06 | 1.4991e-07 | 1(Win) | true |
| simdjson (ondemand) | 4981.01 | 0.0790807 | 5279.08ms | 500299 | 160 | 918093 | 95788.3 | 0.00187911 | 1.03372 | 5.48437 | 0.717925 | 0.0011865 | 7.82032e-06 | 8.61985e-07 | 2(Loss) | true |
