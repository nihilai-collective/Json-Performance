
----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 815.91 | 0.131489 | 5011.42ms | 676745 | 80 | 8.65435e+07 | 791011 | 0.170534 | 3.72476 | 1(Win) | true |
| simdjson (ondemand) | 546.359 | 0.23482 | 7432.13ms | 676745 | 160 | 1.23108e+09 | 1.18126e+06 | 0.137481 | 5.56246 | 2(Loss) | true |
