
----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1767.28 | 0.561737 | 7119.91ms | 264040 | 80 | 5.1249e+07 | 142483 | 0.424316 | 1.40051 | 1(Win) | true |
| Jsonifier (generic) | 1700.42 | 0.153672 | 7582.87ms | 264040 | 160 | 8.28588e+06 | 148086 | 0.255092 | 1.4556 | 2(Loss) | true |
