
----
### Instruments Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5576.03 | 0.0382115 | 2596.85ms | 108313 | 1280 | 64137.1 | 18524.9 | 0.157315 | 0.917492 | 5.07929 | 0.763934 | 0.00070576 | 2.65434e-06 | 9.95379e-07 | 1(Win) | true |
| simdjson (ondemand) | 4665.75 | 0.0198529 | 2956.8ms | 108313 | 4890 | 94465.6 | 22139 | 0.0960923 | 1.0941 | 5.74251 | 0.727688 | 0.00137854 | 2.40536e-06 | 5.79627e-07 | 2(Loss) | true |
