
----
### Twitter Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 833.623 | 0.126634 | 5264.25ms | 360584 | 320 | 8.73222e+07 | 412512 | 0.498317 | 1(Win) | true |
| simdjson (ondemand) | 264.37 | 0.118344 | 8343.32ms | 360584 | 320 | 7.58287e+08 | 1.30075e+06 | 0.145112 | 2(Loss) | true |
