
----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1857.14 | 0.341196 | 8790.68ms | 124597 | 1280 | 6.10021e+07 | 63982.8 | 0.926247 | 1(Win) | true |
| Jsonifier (two-stage) | 1558.65 | 0.333673 | 5199.52ms | 124597 | 2560 | 1.65653e+08 | 76235.8 | 1.11986 | 2(Loss) | true |
| Glaze | 1431.38 | 1.41563 | 5082.59ms | 124597 | 40 | 5.52418e+07 | 83014.4 | 1.07273 | 3(Loss) | true |
| simdjson (reflection) | 1241.99 | 0.407768 | 6093.56ms | 124597 | 1280 | 1.94812e+08 | 95673 | 0.822191 | 4(Loss) | true |
| simdjson (ondemand) | 1041.38 | 0.514167 | 7188.52ms | 124597 | 640 | 2.20286e+08 | 114104 | 0.196976 | 5(Loss) | true |
