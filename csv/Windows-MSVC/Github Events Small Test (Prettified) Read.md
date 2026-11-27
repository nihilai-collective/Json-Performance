
----
### Github Events Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 977.722 | 0.156998 | 215.698ms | 2158 | 1280 | 13978.9 | 2104.92 | 0.329239 | 3.08012 | 1(Win) | true |
| simdjson (ondemand) | 921.506 | 0.39196 | 239.453ms | 2158 | 30 | 2298.85 | 2233.33 | 0 | 3.28061 | 2(Loss) | true |
