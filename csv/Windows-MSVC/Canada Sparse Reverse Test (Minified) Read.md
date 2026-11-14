
----
### Canada Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6162.79 | 0.0950273 | 8250.56ms | 2090234 | 640 | 6.04661e+07 | 323458 | 0.186933 | 0.493092 | 1(Win) | true |
| simdjson (ondemand) | 5054.56 | 0.0739407 | 5012.34ms | 2090234 | 640 | 5.44214e+07 | 394377 | 0.120271 | 0.601227 | 2(Loss) | true |
