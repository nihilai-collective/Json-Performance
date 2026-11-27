
----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1475.21 | 0.584541 | 5972.81ms | 360584 | 160 | 2.97069e+08 | 233106 | 0.0396972 | 2.05993 | 1(Win) | true |
| simdjson (ondemand) | 1242.93 | 0.367024 | 7056.11ms | 360584 | 640 | 6.59911e+08 | 276668 | 0.18479 | 2.44499 | 2(Loss) | true |
