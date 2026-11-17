
----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 532.85 | 0.101572 | 6026.67ms | 264040 | 80 | 1.84318e+07 | 472569 | 0.0606099 | 5.70352 | 1(Win) | true |
| simdjson (ondemand) | 210.624 | 0.122429 | 7536.17ms | 264040 | 320 | 6.85554e+08 | 1.19553e+06 | 0.0669492 | 14.4303 | 2(Loss) | true |
