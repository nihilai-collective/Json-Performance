
----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2426.06 | 0.0794423 | 5413.16ms | 466906 | 640 | 1.36063e+07 | 183539 | 0.208813 | 1.02033 | 1(Win) | true |
| Glaze | 2115.33 | 0.0512153 | 6081.38ms | 466906 | 1280 | 1.48769e+07 | 210500 | 0.130271 | 1.17026 | 2(Loss) | true |
| Jsonifier (two-stage) | 2017.33 | 0.0562455 | 6398.7ms | 466906 | 1280 | 1.97284e+07 | 220726 | 0.110749 | 1.22707 | 3(Loss) | true |
| simdjson (ondemand) | 1026.4 | 0.110334 | 5941.62ms | 466906 | 80 | 1.83288e+07 | 433824 | 0.0309246 | 2.41195 | 4(Loss) | true |
