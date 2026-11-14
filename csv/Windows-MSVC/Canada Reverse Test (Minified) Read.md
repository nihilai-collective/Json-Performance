
----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 170.566 | 0.542576 | 8219.53ms | 2090234 | 40 | 1.60838e+11 | 1.1687e+07 | 1.92102 | 14.5148 | 1(Win) | true |
| simdjson (ondemand) | 165.497 | 0.413585 | 8555.11ms | 2090234 | 40 | 9.92659e+10 | 1.2045e+07 | 1.08338 | 14.9594 | 2(Loss) | true |
