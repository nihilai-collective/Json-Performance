
----
### Random Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 18604 | 0.0935557 | 4447.79ms | 837491 | 40 | 64527.8 | 42931.2 | 0.158762 | 1(Win) | true |
| Glaze | 2737.29 | 0.151098 | 7582.11ms | 837491 | 160 | 3.10995e+07 | 291782 | 0.00329023 | 2(Loss) | true |
| simdjson (reflection) | 356.822 | 0.12863 | 6992.88ms | 837491 | 160 | 1.32636e+09 | 2.23836e+06 | 0.519669 | 3(Loss) | true |
