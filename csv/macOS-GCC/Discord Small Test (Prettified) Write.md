
----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11657.7 | 1.16783 | 64.6948ms | 7376 | 4890 | 242822 | 603.406 | 0.433777 | 1(Win) | true |
| Glaze | 2245.66 | 0.782949 | 327.106ms | 7376 | 640 | 384947 | 3132.4 | 0.655527 | 2(Loss) | true |
| simdjson (reflection) | 289.035 | 0.509843 | 2343.73ms | 7376 | 640 | 9.85359e+06 | 24337.2 | 1.18398 | 3(Loss) | true |
