
----
### Random Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1490.61 | 0.0763917 | 6688.28ms | 409725 | 320 | 1.28321e+07 | 262137 | 0.029812 | 2.03882 | 1(Win) | true |
| simdjson (ondemand) | 1243.01 | 0.137497 | 8058.83ms | 409725 | 320 | 5.97824e+07 | 314353 | 0.139874 | 2.44498 | 2(Loss) | true |
