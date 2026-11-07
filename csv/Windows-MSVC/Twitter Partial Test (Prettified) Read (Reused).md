
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10220.4 | 0.183732 | 6088.6ms | 631514 | 640 | 7.502e+06 | 58926.9 | 0.0487655 | 0.242078 | 1(Win) | true |
| Jsonifier (two-stage) | 10123.5 | 0.406438 | 6197.72ms | 631514 | 160 | 9.35439e+06 | 59491.2 | 0.0252074 | 0.244418 | 2(Loss) | true |
| simdjson (ondemand) | 3901.81 | 0.0769227 | 7970.23ms | 631514 | 1280 | 1.80448e+07 | 154354 | 0.0847577 | 0.634384 | 3(Loss) | true |
| Glaze | 3649.51 | 0.0582359 | 8591.75ms | 631514 | 2560 | 2.36439e+07 | 165025 | 0.0408863 | 0.678292 | 4(Loss) | true |
