
----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1141.45 | 0.23622 | 7239.84ms | 676745 | 40 | 7.13557e+07 | 565415 | 0.240834 | 2.66237 | 1(Win) | true |
| simdjson (ondemand) | 963.606 | 0.294145 | 8563.9ms | 676745 | 30 | 1.16438e+08 | 669770 | 0.116819 | 3.15379 | 2(Loss) | true |
