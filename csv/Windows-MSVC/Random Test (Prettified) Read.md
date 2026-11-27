
----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1167.14 | 0.227351 | 7295.11ms | 676745 | 320 | 5.05767e+08 | 552972 | 0.276148 | 2.12115 | 1(Win) | true |
| simdjson (ondemand) | 970.686 | 0.432136 | 8650.96ms | 676745 | 40 | 3.30213e+08 | 664885 | 0.0553674 | 2.5504 | 2(Loss) | true |
