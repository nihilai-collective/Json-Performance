
----
### Random Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1451.45 | 0.609774 | 6750.6ms | 409725 | 640 | 1.72465e+09 | 269210 | 0.542292 | 2.09382 | 1(Win) | true |
| simdjson (ondemand) | 1175.77 | 0.299843 | 8495.12ms | 409725 | 1280 | 1.27098e+09 | 332330 | 0.0360982 | 2.58476 | 2(Loss) | true |
