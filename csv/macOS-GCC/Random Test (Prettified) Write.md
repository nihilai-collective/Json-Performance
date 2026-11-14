
----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14613.7 | 0.122337 | 5503.4ms | 837491 | 2560 | 1.14444e+07 | 54653.6 | 0.467308 | 1(Win) | true |
| Glaze | 2516.16 | 0.145099 | 8257.54ms | 837491 | 640 | 1.35766e+08 | 317426 | 0.668277 | 2(Loss) | true |
| simdjson (reflection) | 319.74 | 0.261848 | 7851.61ms | 837491 | 80 | 3.42259e+09 | 2.49795e+06 | 0.0828154 | 3(Loss) | true |
