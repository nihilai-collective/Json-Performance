
----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 2132.43 | 0.133371 | 2534.88ms | 56369 | 1280 | 1.44698e+06 | 25209.6 | 0.278213 | 1.15978 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2126.17 | 0.235617 | 2571.17ms | 56369 | 640 | 2.27131e+06 | 25283.8 | 0.256029 | 1.16317 | 1(Tie) | true |
