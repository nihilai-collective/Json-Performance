
----
### Random Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2573.85 | 0.0395176 | 7782.18ms | 409725 | 2560 | 9.21386e+06 | 151813 | 0.0677413 | 0.961724 | 1(Win) | true |
| simdjson (ondemand) | 1965.23 | 0.0972032 | 5034.33ms | 409725 | 320 | 1.19527e+07 | 198828 | 0.332013 | 1.25951 | 2(Loss) | true |
