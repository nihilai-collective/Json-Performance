
----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 182.502 | 0.333206 | 2534.71ms | 4630 | 320 | 2.07972e+06 | 24194.4 | 0.181155 | 13.5488 | 1(Win) | true |
| simdjson (ondemand) | 174.572 | 0.165694 | 2593.72ms | 4630 | 2560 | 4.49641e+06 | 25293.4 | 1.21582 | 14.1652 | 2(Loss) | true |
