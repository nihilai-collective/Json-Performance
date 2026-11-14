
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 668.931 | 0.338345 | 7500.89ms | 409725 | 160 | 6.24975e+08 | 584132 | 0.921652 | 3.70081 | 1(Win) | true |
| simdjson (ondemand) | 598.854 | 0.323174 | 8556.33ms | 409725 | 160 | 7.11436e+08 | 652487 | 0.708543 | 4.13394 | 2(Loss) | true |
