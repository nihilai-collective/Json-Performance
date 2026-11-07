
----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1081.49 | 0.361881 | 5620.7ms | 124597 | 640 | 1.01177e+08 | 109871 | 0.0935205 | 2.28868 | 1(Win) | true |
| Jsonifier | 1041.13 | 0.954016 | 5910.03ms | 124597 | 160 | 1.89686e+08 | 114131 | 1.07319 | 2.37744 | 2(Loss) | true |
| Glaze | 997.801 | 0.304726 | 6148.36ms | 124597 | 1280 | 1.68561e+08 | 119087 | 0.136792 | 2.48064 | 3(Loss) | true |
| simdjson (ondemand) | 962.561 | 0.146219 | 6327.45ms | 124597 | 2560 | 8.34076e+07 | 123447 | 0.0187046 | 2.57154 | 4(Loss) | true |
