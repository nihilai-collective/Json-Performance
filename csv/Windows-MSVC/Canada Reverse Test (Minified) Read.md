
----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 385.366 | 1.0291 | 7787.48ms | 2090234 | 30 | 8.50123e+10 | 5.17275e+06 | 0.566137 | 7.88679 | 1(Win) | true |
| simdjson (ondemand) | 352.751 | 0.637564 | 8522.71ms | 2090234 | 80 | 1.03846e+11 | 5.65102e+06 | 0.267178 | 8.61601 | 2(Loss) | true |
