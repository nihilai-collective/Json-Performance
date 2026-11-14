
----
### CitmCatalog Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5540.33 | 0.0100882 | 9356.78ms | 500299 | 4890 | 369085 | 86118 | 0.059727 | 0.928876 | 4.96274 | 0.714799 | 0.000903672 | 6.94554e-06 | 5.97598e-07 | 1(Win) | true |
| simdjson (ondemand) | 4918.4 | 0.0739848 | 5334.07ms | 500299 | 2560 | 1.31867e+07 | 97007.6 | 0.174445 | 1.04257 | 5.6204 | 0.717847 | 0.00101706 | 1.12901e-05 | 1.39448e-06 | 2(Loss) | true |
