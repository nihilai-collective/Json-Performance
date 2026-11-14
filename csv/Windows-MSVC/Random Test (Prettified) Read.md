
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1103.94 | 0.150427 | 7438.78ms | 676745 | 640 | 4.94989e+08 | 584630 | 0.105038 | 2.75272 | 1(Win) | true |
| simdjson (ondemand) | 953.914 | 0.230613 | 8604.33ms | 676745 | 80 | 1.94756e+08 | 676575 | 0.122457 | 3.1856 | 2(Loss) | true |
