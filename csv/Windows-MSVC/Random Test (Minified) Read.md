
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 713.931 | 0.176777 | 6971.43ms | 409725 | 320 | 2.99553e+08 | 547313 | 0.30539 | 4.25661 | 1(Win) | true |
| simdjson (ondemand) | 596.212 | 0.257177 | 8292.99ms | 409725 | 640 | 1.81814e+09 | 655378 | 0.040204 | 5.09715 | 2(Loss) | true |
