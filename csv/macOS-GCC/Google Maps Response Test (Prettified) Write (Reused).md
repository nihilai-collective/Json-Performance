
----
### Google Maps Response Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 21107.6 | 0.519792 | 142.705ms | 31235 | 4890 | 263132 | 1411.25 | 0.420138 | 1(Win) | true |
| Glaze | 3317.45 | 0.116416 | 913.244ms | 31235 | 320 | 34966.2 | 8979.2 | 0.0534855 | 2(Loss) | true |
| simdjson (reflection) | 340.108 | 0.205403 | 9370.23ms | 31235 | 320 | 1.03565e+07 | 87584 | 0.0949044 | 3(Loss) | true |
