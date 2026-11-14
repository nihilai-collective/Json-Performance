
----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2035.34 | 0.131461 | 2738.6ms | 56369 | 4890 | 5.8953e+06 | 26412.1 | 1.66419 | 1(Win) | true |
| simdjson (ondemand) | 1493.11 | 0.185061 | 3597.98ms | 56369 | 4890 | 2.17088e+07 | 36003.9 | 0.284539 | 2(Loss) | true |
