
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1579.05 | 0.240982 | 5025.51ms | 631514 | 80 | 6.75823e+07 | 381405 | 0.159534 | 1.5677 | 1(Win) | true |
| Jsonifier | 1380.2 | 0.465522 | 5595.36ms | 631514 | 320 | 1.32041e+09 | 436355 | 0.489664 | 1.79361 | 2(Loss) | true |
| Glaze | 1336.56 | 0.55323 | 5721.74ms | 631514 | 320 | 1.98861e+09 | 450603 | 0.0641914 | 1.85219 | 3(Loss) | true |
| simdjson (ondemand) | 1213.45 | 0.329858 | 6308.95ms | 631514 | 640 | 1.71538e+09 | 496321 | 0.39482 | 2.04009 | 4(Loss) | true |
