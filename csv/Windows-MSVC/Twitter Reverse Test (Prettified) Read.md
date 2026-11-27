
----
### Twitter Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 710.917 | 0.29322 | 6179.17ms | 360584 | 160 | 3.21871e+08 | 483713 | 0.545244 | 4.27496 | 1(Win) | true |
| simdjson (ondemand) | 297.401 | 0.255746 | 7286.81ms | 360584 | 160 | 1.39915e+09 | 1.15628e+06 | 0.278243 | 10.2194 | 2(Loss) | true |
