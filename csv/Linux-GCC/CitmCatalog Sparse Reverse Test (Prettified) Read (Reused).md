
----
### CitmCatalog Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5744.84 | 0.333897 | 5034.07ms | 1151920 | 30 | 1.22302e+07 | 191225 | 0.211699 | 0.879538 | 4.78653 | 0.810227 | 0.0012465 | 0.00378441 | 1.59155e-06 | 1(Win) | true |
| simdjson (ondemand) | 5409.45 | 0.120594 | 5512.66ms | 1151920 | 80 | 4.79823e+06 | 203081 | 1.04742 | 0.944287 | 5.1783 | 0.783046 | 0.00160319 | 0.0113588 | 9.54927e-06 | 2(Loss) | true |
