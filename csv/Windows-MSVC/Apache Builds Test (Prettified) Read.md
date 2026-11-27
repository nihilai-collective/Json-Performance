
----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 931.601 | 0.696123 | 6673.36ms | 124597 | 1280 | 1.00911e+09 | 127549 | 0.206658 | 2.65684 | 1(Win) | true |
| simdjson (ondemand) | 877.52 | 0.299267 | 7191.09ms | 124597 | 1280 | 2.10198e+08 | 135410 | 0.362163 | 2.82067 | 2(Loss) | true |
| Jsonifier (two-stage) | 838.882 | 0.497508 | 6847.27ms | 124597 | 640 | 3.17829e+08 | 141647 | 2.07359 | 2.95067 | 3(Loss) | true |
| Glaze | 821.409 | 0.599934 | 7546.46ms | 124597 | 1280 | 9.6408e+08 | 144660 | 0.386158 | 3.01331 | 4(Loss) | true |
