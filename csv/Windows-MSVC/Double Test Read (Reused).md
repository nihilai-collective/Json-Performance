
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 676.632 | 0.155154 | 256.345ms | 1811 | 160 | 2509.43 | 2552.5 | 0.492126 | 3.61856 | 1(Win) | true |
| simdjson (ondemand) | 351.445 | 0.342867 | 512.115ms | 1811 | 1280 | 363400 | 4914.3 | 0.394287 | 7.00653 | 2(Loss) | true |
