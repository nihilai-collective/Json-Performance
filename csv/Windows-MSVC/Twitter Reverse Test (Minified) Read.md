
----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 539.597 | 0.256507 | 5997.45ms | 264040 | 30 | 4.29852e+07 | 466660 | 0.556183 | 5.63214 | 1(Win) | true |
| simdjson (ondemand) | 207.169 | 0.325881 | 7669.83ms | 264040 | 80 | 1.25516e+09 | 1.21547e+06 | 0.0560795 | 14.6702 | 2(Loss) | true |
