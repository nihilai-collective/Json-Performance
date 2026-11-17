
----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 803.962 | 0.246503 | 5107.87ms | 676745 | 160 | 6.26533e+08 | 802767 | 0.447877 | 3.78005 | 1(Win) | true |
| simdjson (ondemand) | 530.911 | 1.16384 | 7697.78ms | 676745 | 40 | 8.00674e+09 | 1.21564e+06 | 0.306814 | 5.72422 | 2(Loss) | true |
