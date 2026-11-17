
----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7805.72 | 0.68351 | 185.682ms | 14795 | 1280 | 195391 | 1807.6 | 0.0663423 | 1(Win) | true |
| Glaze | 3331.2 | 0.415924 | 438.48ms | 14795 | 640 | 198627 | 4235.6 | 0.236653 | 2(Loss) | true |
| simdjson (reflection) | 242.252 | 0.17445 | 5693.12ms | 14795 | 4890 | 5.04833e+07 | 58243.6 | 0.0755565 | 3(Loss) | true |
