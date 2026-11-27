
----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 350.411 | 0.13634 | 1302.25ms | 4630 | 320 | 94450.5 | 12600.9 | 0.837751 | 8.65968 | 1(Win) | true |
| simdjson (ondemand) | 346.893 | 0.386342 | 1307.75ms | 4630 | 80 | 193467 | 12728.8 | 0.463694 | 8.75006 | 2(Loss) | true |
