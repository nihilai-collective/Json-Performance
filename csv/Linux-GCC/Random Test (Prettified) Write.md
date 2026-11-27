
----
### Random Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22540.5 | 0.224139 | 3564.43ms | 837491 | 1280 | 8.07379e+06 | 35433.7 | 0.111343 | 0.109741 | 1(Win) | true |
| Glaze | 3741.23 | 0.223827 | 5689.5ms | 837491 | 40 | 9.13307e+06 | 213484 | 0.256017 | 0.661644 | 2(Loss) | true |
| simdjson (reflection) | 568.576 | 0.297771 | 9123.17ms | 837491 | 160 | 2.79943e+09 | 1.40473e+06 | 0.527752 | 4.35426 | 3(Loss) | true |
