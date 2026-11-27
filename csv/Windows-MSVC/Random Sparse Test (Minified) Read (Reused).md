
----
### Random Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1731.18 | 0.302293 | 6427.74ms | 409725 | 1280 | 5.9589e+08 | 225709 | 1.67646 | 1.75543 | 1(Win) | true |
| simdjson (ondemand) | 1352.72 | 0.196823 | 8132.53ms | 409725 | 320 | 1.03436e+08 | 288857 | 0.118322 | 2.24673 | 2(Loss) | true |
