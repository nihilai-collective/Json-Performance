
----
### Github Events Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4151.02 | 0.172003 | 1235.31ms | 53331 | 160 | 71062.9 | 12252.5 | 0.071465 | 0.730822 | 1(Win) | true |
| simdjson (ondemand) | 3055.48 | 0.170607 | 1688.42ms | 53331 | 160 | 129037 | 16645.6 | 0.0338041 | 0.99303 | 2(Loss) | true |
