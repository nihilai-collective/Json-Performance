
----
### Random Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1430.77 | 0.0288776 | 334.403ms | 4926 | 640 | 575.374 | 3283.4 | 0.0620931 | 1(Win) | true |
| simdjson (ondemand) | 1012.31 | 0.10017 | 521.157ms | 4926 | 80 | 1728.75 | 4640.69 | 0.045542 | 2(Loss) | true |
