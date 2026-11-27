
----
### CitmCatalog Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8609.85 | 0.267232 | 7087.31ms | 1151920 | 40 | 4.65041e+06 | 127593 | 0.0481645 | 0.597951 | 2.81771 | 0.375609 | 0.000946246 | 0.0081181 | 2.86478e-06 | 1(Win) | true |
| simdjson (ondemand) | 8237.84 | 0.109167 | 7232.72ms | 1151920 | 1280 | 2.71276e+07 | 133355 | 0.271869 | 0.615878 | 3.07884 | 0.347429 | 0.00110744 | 0.0111096 | 8.27762e-06 | 2(Loss) | true |
