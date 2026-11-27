
----
### CitmCatalog Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5524.18 | 0.0400186 | 799.359ms | 5092 | 4890 | 605.166 | 879.065 | 0.131593 | 0.973385 | 4.47059 | 0.666546 | 0.00131595 | 1.05221e-05 | 3.45383e-06 | 1(Win) | true |
| simdjson (ondemand) | 4547.35 | 0.148602 | 823.854ms | 5092 | 640 | 1611.73 | 1067.9 | 0.0419749 | 1.17283 | 5.27494 | 0.643363 | 0.000828505 | 5.21652e-06 | 0 | 2(Loss) | true |
