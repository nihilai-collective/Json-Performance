
----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1869.01 | 0.257277 | 164.943ms | 2889 | 4890 | 70337 | 1474.13 | 0.113412 | 1.29975 | 1(Win) | true |
| Glaze | 1607.68 | 0.226084 | 192.988ms | 2889 | 80 | 1200.95 | 1713.75 | 0.0729927 | 1.51687 | 2(Loss) | true |
| Jsonifier (two-stage) | 1543.51 | 0.32032 | 204.898ms | 2889 | 40 | 1307.69 | 1785 | 0.0934579 | 1.57539 | 3(Loss) | true |
| simdjson (ondemand) | 1363.94 | 0.15704 | 224.27ms | 2889 | 160 | 1610.06 | 2020 | 0.0618429 | 1.79465 | 4(Loss) | true |
