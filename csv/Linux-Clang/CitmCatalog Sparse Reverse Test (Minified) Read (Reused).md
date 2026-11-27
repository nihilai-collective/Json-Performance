
----
### CitmCatalog Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3069.63 | 0.0416011 | 8359.93ms | 500299 | 640 | 2.67595e+06 | 155433 | 0.107048 | 1.66405 | 9.80264 | 1.81321 | 0.0019992 | 1.1996e-05 | 1.09341e-05 | 1(Win) | true |
| simdjson (ondemand) | 2888.5 | 0.106059 | 8796.01ms | 500299 | 640 | 1.96422e+07 | 165180 | 0.166837 | 1.76117 | 10.0943 | 1.72189 | 0.00223576 | 7.52363e-06 | 5.57791e-06 | 2(Loss) | true |
