
----
### CitmCatalog Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8709.26 | 0.0673757 | 6835.63ms | 1151920 | 30 | 216676 | 126137 | 0.0706082 | 0.580448 | 2.87229 | 0.333502 | 0.000562481 | 0.00713157 | 4.16696e-06 | 1(Win) | true |
| simdjson (ondemand) | 8045.96 | 0.0597407 | 7366.72ms | 1151920 | 640 | 4.25804e+06 | 136535 | 0.567605 | 0.628649 | 3.20446 | 0.344805 | 0.000857526 | 0.00957411 | 8.65132e-06 | 2(Loss) | true |
