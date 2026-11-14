
----
### Canada Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 6027.51 | 0.124188 | 5260.06ms | 5212421 | 40 | 4.19588e+07 | 824710 | 0.0161032 | 1(Win) | true |
| simdjson (ondemand) | 4803.51 | 0.0654333 | 6711.86ms | 5212421 | 320 | 1.46727e+08 | 1.03486e+06 | 0.706494 | 2(Loss) | true |
