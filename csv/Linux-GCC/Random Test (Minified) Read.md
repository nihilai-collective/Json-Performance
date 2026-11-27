
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1283.26 | 0.0432851 | 7819.71ms | 409725 | 1280 | 2.22352e+07 | 304493 | 0.0288383 | 1.92904 | 1(Win) | true |
| simdjson (ondemand) | 1172.54 | 0.0480551 | 8516.67ms | 409725 | 640 | 1.64131e+07 | 333246 | 0.120795 | 2.11123 | 2(Loss) | true |
