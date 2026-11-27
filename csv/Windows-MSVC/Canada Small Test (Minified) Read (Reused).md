
----
### Canada Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 397.503 | 0.155704 | 1262.33ms | 4630 | 640 | 191452 | 11108.1 | 0.115211 | 7.63141 | 1(Win) | true |
| simdjson (ondemand) | 383.963 | 0.503038 | 1281.31ms | 4630 | 640 | 2.14174e+06 | 11499.8 | 0.481938 | 7.89968 | 2(Loss) | true |
