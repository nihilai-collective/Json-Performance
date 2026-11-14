
----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1530.79 | 0.0515585 | 3512.48ms | 56369 | 2560 | 839248 | 35117.6 | 0.00589571 | 1.98398 | 1(Win) | true |
| simdjson (ondemand) | 1373.01 | 0.0679766 | 3908.19ms | 56369 | 2560 | 1.81341e+06 | 39153.3 | 0.197732 | 2.21221 | 2(Loss) | true |
