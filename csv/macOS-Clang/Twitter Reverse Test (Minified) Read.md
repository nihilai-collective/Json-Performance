
----
### Twitter Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 654.45 | 0.114152 | 9912.47ms | 264040 | 320 | 6.17309e+07 | 384763 | 0.215043 | 1(Win) | true |
| simdjson (ondemand) | 194.626 | 0.117648 | 8231.52ms | 264040 | 160 | 3.707e+08 | 1.2938e+06 | 0.121228 | 2(Loss) | true |
