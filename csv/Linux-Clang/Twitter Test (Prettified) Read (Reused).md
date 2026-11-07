
----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2859.53 | 0.0694276 | 6333.06ms | 631514 | 1280 | 2.73686e+07 | 210615 | 0.0393203 | 0.865659 | 1(Win) | true |
| Glaze | 2188.95 | 0.293269 | 7725.15ms | 631514 | 40 | 2.60427e+07 | 275136 | 0.246969 | 1.13092 | 2(Loss) | true |
| Jsonifier | 1956.14 | 0.0979848 | 8711.34ms | 631514 | 320 | 2.91229e+07 | 307882 | 0.323782 | 1.26553 | 3(Loss) | true |
| simdjson (ondemand) | 1357.54 | 0.0582206 | 5975.78ms | 631514 | 640 | 4.26967e+07 | 443639 | 0.0459801 | 1.82361 | 4(Loss) | true |
