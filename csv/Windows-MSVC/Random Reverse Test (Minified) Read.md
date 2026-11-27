
----
### Random Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 497.147 | 0.343421 | 5215.22ms | 409725 | 40 | 2.91427e+08 | 785972 | 0.0840078 | 4.97983 | 1(Win) | true |
| simdjson (ondemand) | 243.479 | 0.330456 | 5058.3ms | 409725 | 30 | 8.43743e+08 | 1.60484e+06 | 1.07015 | 10.1667 | 2(Loss) | true |
