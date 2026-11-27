
----
### Discord Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1714.26 | 0.108958 | 3145.14ms | 56369 | 2560 | 2.98871e+06 | 31359.1 | 0.155795 | 1(Win) | true |
| simdjson (ondemand) | 966.019 | 0.0820607 | 5576.03ms | 56369 | 2560 | 5.3385e+06 | 55648.6 | 0.125932 | 2(Loss) | true |
