
----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1832.79 | 0.14055 | 5314.62ms | 360584 | 1280 | 8.90145e+07 | 187626 | 0.0913553 | 1.65805 | 1(Win) | true |
| simdjson (ondemand) | 1616.94 | 0.117984 | 5953.86ms | 360584 | 640 | 4.02952e+07 | 212673 | 0.147456 | 1.87941 | 2(Loss) | true |
