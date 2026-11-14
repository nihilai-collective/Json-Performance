
----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2740.02 | 0.0725681 | 916.275ms | 25388 | 40 | 1644.76 | 8836.4 | 0.279497 | 1(Win) | true |
| simdjson (ondemand) | 2433.36 | 0.127588 | 1010.45ms | 25388 | 30 | 4834.86 | 9949.97 | 0.252227 | 2(Loss) | true |
