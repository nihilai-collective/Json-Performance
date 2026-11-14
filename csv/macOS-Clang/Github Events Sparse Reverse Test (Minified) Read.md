
----
### Github Events Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3669.26 | 0.303762 | 1420.93ms | 53331 | 640 | 1.13462e+06 | 13861.2 | 0.459721 | 1(Win) | true |
| simdjson (ondemand) | 2470.48 | 0.204361 | 2076.22ms | 53331 | 1280 | 2.2657e+06 | 20587.3 | 2.3852 | 2(Loss) | true |
