
----
### Google Maps Response Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2067.39 | 0.179153 | 447.74ms | 9378 | 4890 | 293719 | 4326.01 | 0.144344 | 1.18943 | 1(Win) | true |
| Jsonifier | 2055.4 | 0.118796 | 456.47ms | 9378 | 160 | 4275.16 | 4351.25 | 0.0861079 | 1.19751 | 2(Loss) | true |
| Glaze | 1447 | 0.2071 | 628.999ms | 9378 | 2560 | 419453 | 6180.74 | 0.0347481 | 1.70301 | 3(Loss) | true |
| simdjson (ondemand) | 1086.06 | 0.266834 | 860.359ms | 9378 | 1280 | 618019 | 8234.84 | 0.168586 | 2.27228 | 4(Loss) | true |
