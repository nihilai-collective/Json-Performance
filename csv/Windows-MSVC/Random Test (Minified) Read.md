
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 686.881 | 0.305386 | 7479.12ms | 409725 | 80 | 2.4144e+08 | 568868 | 0.836289 | 3.6041 | 1(Win) | true |
| simdjson (ondemand) | 601.37 | 0.989439 | 8572.58ms | 409725 | 30 | 1.23994e+09 | 649757 | 0.366482 | 4.11647 | 2(Loss) | true |
