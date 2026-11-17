
----
### Apache Builds Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2490.12 | 0.0397636 | 4376.94ms | 94653 | 640 | 132978 | 36250.5 | 0.0420904 | 2.03568 | 9.3863 | 1.79966 | 0.00478536 | 4.07739e-06 | 8.25383e-07 | 1(Win) | true |
| simdjson (ondemand) | 1873.02 | 0.0474274 | 5572.81ms | 94653 | 640 | 334367 | 48194 | 0.253499 | 2.72712 | 11.0178 | 1.95328 | 0.00864785 | 4.20945e-06 | 1.15554e-06 | 2(Loss) | true |
