
----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2760.57 | 0.242696 | 344.476ms | 9378 | 40 | 2472.91 | 3239.75 | 0.0210966 | 1(Win) | true |
| simdjson (ondemand) | 2375.08 | 0.26517 | 402.47ms | 9378 | 40 | 3988.15 | 3765.57 | 0.120756 | 2(Loss) | true |
