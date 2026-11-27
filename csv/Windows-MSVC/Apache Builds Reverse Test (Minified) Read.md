
----
### Apache Builds Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 648.406 | 0.323597 | 7146.92ms | 94653 | 2560 | 5.19545e+08 | 139215 | 1.00027 | 4.68628 | 1(Win) | true |
| simdjson (ondemand) | 483.204 | 0.287212 | 9523.25ms | 94653 | 2560 | 7.36976e+08 | 186812 | 0.0151575 | 6.28879 | 2(Loss) | true |
