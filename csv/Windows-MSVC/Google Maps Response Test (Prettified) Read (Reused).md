
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2472.14 | 0.320782 | 1095.31ms | 25388 | 1280 | 1.2634e+06 | 9793.91 | 0.0382745 | 0.998581 | 1(Win) | true |
| Jsonifier | 2444.41 | 0.0804268 | 1114.52ms | 25388 | 40 | 2538.46 | 9905 | 0.0168294 | 1.00994 | 2(Loss) | true |
| Glaze | 1633.68 | 0.362138 | 1609.19ms | 25388 | 640 | 1.84354e+06 | 14820.5 | 0.041134 | 1.51246 | 3(Loss) | true |
| simdjson (ondemand) | 1204.97 | 0.11915 | 2211.59ms | 25388 | 30 | 17195.4 | 20093.3 | 0.380102 | 2.05183 | 4(Loss) | true |
