
----
### CitmCatalog Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5437.72 | 0.0257273 | 9487.89ms | 500299 | 2560 | 1.30453e+06 | 87743 | 0.0464694 | 0.933957 | 4.95866 | 0.768281 | 0.000964696 | 1.40822e-05 | 1.10044e-05 | 1(Win) | true |
| simdjson (ondemand) | 4870.08 | 0.0292386 | 5387.99ms | 500299 | 1280 | 1.05029e+06 | 97970.1 | 0.000770319 | 1.04629 | 5.63921 | 0.726658 | 0.00109727 | 4.97999e-05 | 4.72842e-06 | 2(Loss) | true |
