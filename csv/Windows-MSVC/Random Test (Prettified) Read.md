
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1157.21 | 0.162761 | 7626.83ms | 728486 | 640 | 6.11073e+08 | 600354 | 0.113943 | 2.62616 | 1(Win) | true |
| Jsonifier | 1052.75 | 0.129126 | 8393.17ms | 728486 | 640 | 4.64732e+08 | 659928 | 0.178111 | 2.88684 | 2(Loss) | true |
| Glaze | 995.091 | 0.156943 | 8867.17ms | 728486 | 640 | 7.68392e+08 | 698165 | 0.272494 | 3.05406 | 3(Loss) | true |
| simdjson (ondemand) | 893.458 | 0.351827 | 9903.05ms | 728486 | 30 | 2.2453e+08 | 777583 | 0.208342 | 3.40148 | 4(Loss) | true |
