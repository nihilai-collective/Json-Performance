
----
### Discord Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3584.79 | 0.0663038 | 182.692ms | 6701 | 320 | 447.073 | 1782.69 | 0.00648556 | 1(Win) | true |
| simdjson (ondemand) | 3370.84 | 0.0532411 | 196.688ms | 6701 | 640 | 652.042 | 1895.84 | 0.304053 | 2(Loss) | true |
