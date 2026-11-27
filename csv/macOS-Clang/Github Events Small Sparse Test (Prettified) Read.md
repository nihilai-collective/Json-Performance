
----
### Github Events Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4349.97 | 0.0613246 | 50.658ms | 2158 | 4890 | 411.632 | 473.114 | 0.0481253 | 1(Win) | true |
| simdjson (ondemand) | 3819.13 | 0.127987 | 57.3873ms | 2158 | 640 | 304.43 | 538.873 | 0.1306 | 2(Loss) | true |
