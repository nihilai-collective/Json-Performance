
----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1189.78 | 0.259221 | 283.083ms | 3370 | 80 | 3922.47 | 2701.25 | 0.0462963 | 2.06099 | 1(Win) | true |
| Jsonifier | 1106.33 | 0.23128 | 301.637ms | 3370 | 4890 | 220736 | 2904.99 | 0.759736 | 2.21648 | 2(Loss) | true |
| Glaze | 1041.95 | 0.234183 | 321.997ms | 3370 | 4890 | 255145 | 3084.5 | 0.0420294 | 2.35517 | 3(Loss) | true |
| simdjson (ondemand) | 853.196 | 0.295014 | 390.693ms | 3370 | 1280 | 158073 | 3766.88 | 0.0581058 | 2.88121 | 4(Loss) | true |
