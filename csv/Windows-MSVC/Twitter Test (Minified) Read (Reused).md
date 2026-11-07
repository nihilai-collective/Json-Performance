
----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1838.19 | 0.232159 | 7162.29ms | 466906 | 80 | 2.53011e+07 | 242236 | 0.179769 | 1.34673 | 1(Win) | true |
| Jsonifier (two-stage) | 1570.37 | 0.136185 | 8301.97ms | 466906 | 320 | 4.77162e+07 | 283549 | 0.0765443 | 1.57631 | 2(Loss) | true |
| Glaze | 1457.9 | 0.534632 | 9448.19ms | 466906 | 40 | 1.06653e+08 | 305422 | 0.206424 | 1.69804 | 3(Loss) | true |
| simdjson (ondemand) | 1174.2 | 0.118978 | 5266.57ms | 466906 | 640 | 1.30281e+08 | 379215 | 0.137389 | 2.1083 | 4(Loss) | true |
