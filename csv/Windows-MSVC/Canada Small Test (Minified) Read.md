
----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 188.131 | 0.0899366 | 2373.86ms | 4630 | 4890 | 2.17883e+06 | 23470.4 | 0.20023 | 13.1416 | 1(Win) | true |
| simdjson (ondemand) | 171.082 | 0.247313 | 2523.1ms | 4630 | 640 | 2.60752e+06 | 25809.4 | 0.125765 | 14.4538 | 2(Loss) | true |
