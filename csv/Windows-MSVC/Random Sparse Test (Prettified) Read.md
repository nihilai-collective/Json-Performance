
----
### Random Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2388.88 | 0.110137 | 6974.27ms | 676745 | 1280 | 1.13329e+08 | 270166 | 0.0209607 | 1.27217 | 1(Win) | true |
| simdjson (ondemand) | 1875.99 | 0.267506 | 8940.18ms | 676745 | 320 | 2.71024e+08 | 344029 | 0.0921919 | 1.62005 | 2(Loss) | true |
