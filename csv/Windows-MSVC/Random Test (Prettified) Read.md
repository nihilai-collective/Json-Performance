
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1141.59 | 0.257541 | 7312.35ms | 676745 | 320 | 6.78375e+08 | 565346 | 0.32458 | 2.16862 | 1(Win) | true |
| simdjson (ondemand) | 976.964 | 0.283584 | 8616.11ms | 676745 | 40 | 1.40384e+08 | 660612 | 0.0863351 | 2.53405 | 2(Loss) | true |
