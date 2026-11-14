
----
### Discord Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3024.14 | 0.0351361 | 2828.26ms | 83958 | 30 | 2596.26 | 26476.5 | 0.0739568 | 1(Win) | true |
| simdjson (ondemand) | 2226.18 | 0.255495 | 3554.46ms | 83958 | 2560 | 2.16176e+07 | 35966.8 | 0.266128 | 2(Loss) | true |
