
----
### Random Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 533.51 | 0.427089 | 9334.71ms | 409725 | 30 | 2.93535e+08 | 732403 | 0.000910237 | 5.69653 | 1(Win) | true |
| simdjson (ondemand) | 340.358 | 0.283233 | 7243.45ms | 409725 | 30 | 3.17192e+08 | 1.14804e+06 | 0.150337 | 8.92886 | 2(Loss) | true |
