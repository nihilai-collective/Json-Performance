
----
### Canada Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 183.245 | 0.462458 | 7697.19ms | 2090234 | 40 | 1.01235e+11 | 1.08784e+07 | 0.368545 | 13.511 | 1(Win) | true |
| simdjson (ondemand) | 173.447 | 1.07059 | 7919.62ms | 2090234 | 30 | 4.54174e+11 | 1.14929e+07 | 0.1931 | 14.2741 | 2(Loss) | true |
