
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 728.566 | 0.159312 | 6825.42ms | 409725 | 320 | 2.33612e+08 | 536319 | 0.00559399 | 4.1714 | 1(Win) | true |
| simdjson (ondemand) | 617.563 | 0.100253 | 8052.18ms | 409725 | 640 | 2.57514e+08 | 632719 | 0.014642 | 4.92115 | 2(Loss) | true |
