
----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1238.09 | 0.173717 | 8118.35ms | 409725 | 30 | 9.01757e+06 | 315603 | 0.10129 | 2.45475 | 1(Win) | true |
| simdjson (ondemand) | 1023.63 | 0.0775606 | 9742.17ms | 409725 | 1280 | 1.122e+08 | 381724 | 0.292812 | 2.96896 | 2(Loss) | true |
