
----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1520.21 | 0.16715 | 6651.92ms | 409725 | 30 | 5.53747e+06 | 257033 | 0.0648004 | 1.99907 | 1(Win) | true |
| simdjson (ondemand) | 1233.65 | 0.0996636 | 8067.75ms | 409725 | 640 | 6.37761e+07 | 316740 | 0.124504 | 2.46359 | 2(Loss) | true |
