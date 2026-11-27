
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 8613.32 | 0.185997 | 45.2114ms | 3808 | 40 | 24.5994 | 421.625 | 0.0888626 | 0.270339 | 1(Win) | true |
| Jsonifier | 8386.56 | 0.0726395 | 45.2844ms | 3808 | 320 | 31.6608 | 433.025 | 0.0461654 | 0.276856 | 2(Loss) | true |
| simdjson (ondemand) | 8201.89 | 0.177323 | 47.0581ms | 3808 | 80 | 49.3158 | 442.775 | 0.0225899 | 0.282908 | 3(Loss) | true |
| Glaze | 4018.88 | 0.103498 | 93.7047ms | 3808 | 30 | 26.2402 | 903.633 | 0.0110652 | 0.598302 | 4(Loss) | true |
