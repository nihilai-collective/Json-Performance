
----
### Twitter Partial Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9156.35 | 0.12921 | 6611.7ms | 631514 | 1280 | 9.24533e+06 | 65775 | 0.384406 | 0.270261 | 1(Win) | true |
| Jsonifier | 8703.15 | 0.097043 | 6919.89ms | 631514 | 2560 | 1.15447e+07 | 69200.1 | 0.013493 | 0.284321 | 2(Loss) | true |
| simdjson (ondemand) | 4115.51 | 0.119453 | 7424.79ms | 631514 | 1280 | 3.91129e+07 | 146339 | 0.79652 | 0.601446 | 3(Loss) | true |
| Glaze | 3532.41 | 0.416414 | 9292.02ms | 631514 | 40 | 2.0162e+07 | 170495 | 0.227251 | 0.700674 | 4(Loss) | true |
