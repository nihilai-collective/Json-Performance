
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 11439.1 | 0.630066 | 3838.81ms | 461466 | 2560 | 1.50421e+08 | 38472.2 | 0.392911 | 0.265368 | 1(Win) | true |
| simdjson (stage-1) | 9668.72 | 0.820932 | 4539.85ms | 461466 | 1280 | 1.78717e+08 | 45516.7 | 0.338356 | 0.313952 | 2(Loss) | true |
