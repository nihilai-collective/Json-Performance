
----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3130.08 | 0.168845 | 209.476ms | 6701 | 30 | 356.506 | 2041.67 | 0.20204 | 1(Win) | true |
| simdjson (ondemand) | 1919.64 | 0.0960327 | 335.263ms | 6701 | 4890 | 49979 | 3329.05 | 0.0293994 | 2(Loss) | true |
