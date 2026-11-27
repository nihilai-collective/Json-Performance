
----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1389.52 | 0.803214 | 8433.2ms | 466906 | 160 | 1.06001e+09 | 320452 | 0.0931407 | 2.18682 | 1(Win) | true |
| Glaze | 1111.47 | 1.32136 | 10082.6ms | 466906 | 160 | 4.48356e+09 | 400618 | 2.0636 | 2.73385 | 2(Loss) | true |
| Jsonifier (two-stage) | 1056.57 | 0.882506 | 5545.8ms | 466906 | 160 | 2.2132e+09 | 421437 | 0.389549 | 2.87596 | 3(Loss) | true |
| simdjson (ondemand) | 885.983 | 0.463466 | 6361.77ms | 466906 | 640 | 3.47236e+09 | 502579 | 0.669712 | 3.42886 | 4(Loss) | true |
