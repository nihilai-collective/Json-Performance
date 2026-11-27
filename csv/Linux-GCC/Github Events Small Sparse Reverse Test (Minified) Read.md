
----
### Github Events Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3452.96 | 0.105862 | 771.495ms | 1691 | 80 | 19.5555 | 467.038 | 0.0454789 | 1.61416 | 6.49911 | 1.16854 | 0.000591366 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2532.46 | 0.0937782 | 786.979ms | 1691 | 320 | 114.118 | 636.797 | 0.0142294 | 2.15186 | 8.47546 | 1.44885 | 0.000611694 | 1.84802e-05 | 1.84802e-06 | 2(Loss) | true |
