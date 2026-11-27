
----
### Twitter Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6026.39 | 0.204973 | 4244.22ms | 264040 | 640 | 4.69457e+06 | 41784.2 | 0.165384 | 0.504004 | 1(Win) | true |
| simdjson (ondemand) | 3789.82 | 0.165489 | 6730.52ms | 264040 | 640 | 7.73789e+06 | 66443.3 | 0.445055 | 0.801631 | 2(Loss) | true |
