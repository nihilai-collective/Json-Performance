
----
### Discord Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1727.88 | 0.329304 | 3183.69ms | 56369 | 320 | 3.35891e+06 | 31112 | 0.531997 | 1(Win) | true |
| simdjson (ondemand) | 1467.25 | 0.240211 | 3842.9ms | 56369 | 160 | 1.23931e+06 | 36638.4 | 0.265679 | 2(Loss) | true |
