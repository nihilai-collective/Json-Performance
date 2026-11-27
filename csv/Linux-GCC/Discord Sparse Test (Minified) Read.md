
----
### Discord Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2515.61 | 0.0863855 | 2140.9ms | 56369 | 4890 | 1.66642e+06 | 21369.7 | 0.383827 | 0.98299 | 1(Win) | true |
| simdjson (ondemand) | 2346.23 | 0.107669 | 2297.79ms | 56369 | 2560 | 1.55797e+06 | 22912.4 | 0.120628 | 1.05404 | 2(Loss) | true |
