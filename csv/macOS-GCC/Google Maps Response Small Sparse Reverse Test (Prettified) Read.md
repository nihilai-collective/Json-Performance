
----
### Google Maps Response Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1687.5 | 0.299314 | 522.2ms | 9378 | 2560 | 644214 | 5299.9 | 1.03515 | 1(Win) | true |
| simdjson (ondemand) | 1543.22 | 0.432712 | 557.35ms | 9378 | 2560 | 1.60992e+06 | 5795.4 | 0.89836 | 2(Loss) | true |
