
----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 700.221 | 0.244118 | 1657.29ms | 11812 | 80 | 123386 | 16087.5 | 0.140056 | 4.33392 | 1(Win) | true |
| simdjson (ondemand) | 569.149 | 0.177873 | 2002.56ms | 11812 | 1280 | 1.58645e+06 | 19792.3 | 0.511799 | 5.33376 | 2(Loss) | true |
