
----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 941.527 | 0.994527 | 401.84ms | 4390 | 160 | 312908 | 4446.64 | 0.0424658 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 929.169 | 0.477879 | 442.111ms | 4390 | 2560 | 1.18691e+06 | 4505.78 | 0.768624 | 1(Tie) | true |
