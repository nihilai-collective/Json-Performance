
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 7184.6 | 0.193408 | 63.9412ms | 3808 | 640 | 611.674 | 505.469 | 0.154799 | 0.326316 | 1(Win) | true |
| Jsonifier | 7093.6 | 0.178498 | 56.2631ms | 3808 | 1280 | 1068.9 | 511.953 | 0.0152625 | 0.329497 | 2(Loss) | true |
| simdjson (ondemand) | 4123.88 | 0.413388 | 93.9335ms | 3808 | 640 | 8481.61 | 880.625 | 1.84315 | 0.578626 | 3(Loss) | true |
| Glaze | 3393.52 | 0.364832 | 112.578ms | 3808 | 2560 | 39023 | 1070.16 | 0.204828 | 0.709831 | 4(Loss) | true |
