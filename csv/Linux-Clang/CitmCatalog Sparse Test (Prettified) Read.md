
----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8627.6 | 0.0410913 | 6877.48ms | 1151920 | 640 | 1.75204e+06 | 127330 | 0.014886 | 0.591532 | 3.03778 | 0.353951 | 0.000949827 | 0.00812867 | 3.89024e-06 | 1(Win) | true |
| simdjson (ondemand) | 8343.52 | 0.0254865 | 7139ms | 1151920 | 1280 | 1.44137e+06 | 131666 | 0.031546 | 0.614989 | 3.07951 | 0.347817 | 0.00116849 | 0.0121733 | 4.53726e-07 | 2(Loss) | true |
