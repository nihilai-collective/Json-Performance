
----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2518.79 | 0.547278 | 4438.64ms | 108313 | 2560 | 1.28953e+08 | 41009.8 | 0.0716805 | 1.20579 | 1(Win) | true |
| Glaze | 1719.01 | 0.302838 | 6465.25ms | 108313 | 640 | 2.11937e+07 | 60090.2 | 0.0418467 | 1.76729 | 2(Loss) | true |
| Jsonifier (two-stage) | 1578.55 | 1.84387 | 6754.28ms | 108313 | 640 | 9.31719e+08 | 65436.7 | 0.344309 | 1.92451 | 3(Loss) | true |
| simdjson (ondemand) | 959.306 | 0.474807 | 5654.54ms | 108313 | 2560 | 6.69146e+08 | 107677 | 0.0966946 | 3.1671 | 4(Loss) | true |
