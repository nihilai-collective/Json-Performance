
----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2863.18 | 0.0871083 | 234.162ms | 6701 | 160 | 604.811 | 2231.98 | 0.0748214 | 1(Win) | true |
| simdjson (ondemand) | 1803.68 | 0.173574 | 367.995ms | 6701 | 30 | 1134.62 | 3543.07 | 0.0423541 | 2(Loss) | true |
