
----
### Twitter Partial Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 4535.82 | 0.0950812 | 90.6253ms | 3808 | 640 | 370.895 | 800.647 | 0.227034 | 1(Win) | true |
| Jsonifier | 4358.57 | 0.0781417 | 89.818ms | 3808 | 320 | 135.65 | 833.206 | 0.0450271 | 2(Loss) | true |
| simdjson (ondemand) | 4091.78 | 0.400592 | 97.3718ms | 3808 | 30 | 379.223 | 887.533 | 0 | 3(Loss) | true |
| Glaze | 2596.66 | 0.123636 | 142.752ms | 3808 | 4890 | 14620.5 | 1398.56 | 0.00395714 | 4(Loss) | true |
