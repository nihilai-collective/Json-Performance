
----
### Apache Builds Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1587.7 | 0.545711 | 7494.68ms | 124597 | 1280 | 2.13509e+08 | 74841.1 | 0.598784 | 1.91349 | 1(Win) | true |
| simdjson (ondemand) | 1507.68 | 0.0786271 | 7891.25ms | 124597 | 4890 | 1.8778e+07 | 78813 | 0.110997 | 2.01517 | 2(Loss) | true |
