
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 710.104 | 0.423569 | 7034.82ms | 409725 | 30 | 1.62971e+08 | 550263 | 0.189966 | 4.27965 | 1(Win) | true |
| simdjson (ondemand) | 599.392 | 0.187825 | 8287.48ms | 409725 | 640 | 9.59511e+08 | 651901 | 0.0486082 | 5.07015 | 2(Loss) | true |
