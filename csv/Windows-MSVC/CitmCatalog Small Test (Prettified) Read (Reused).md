
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1234.23 | 0.07951 | 857.269ms | 9739 | 2560 | 91647.1 | 7525.2 | 0.391362 | 2.456 | 1(Win) | true |
| Jsonifier (generic) | 1214.49 | 0.185487 | 859.012ms | 9739 | 160 | 32195 | 7647.5 | 0.277099 | 2.49402 | 2(Loss) | true |
