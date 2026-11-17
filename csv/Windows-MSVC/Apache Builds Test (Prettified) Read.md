
----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1018.57 | 0.748977 | 6155.37ms | 124597 | 320 | 2.44301e+08 | 116659 | 0.254101 | 2.43007 | 1(Win) | true |
| Jsonifier | 962.099 | 0.848924 | 6446.99ms | 124597 | 320 | 3.51774e+08 | 123506 | 0.611737 | 2.57266 | 2(Loss) | true |
| Glaze | 897.53 | 0.348496 | 6967.46ms | 124597 | 2560 | 5.44945e+08 | 132391 | 0.00395388 | 2.7578 | 3(Loss) | true |
| simdjson (ondemand) | 867.35 | 0.455249 | 6883.4ms | 124597 | 1280 | 4.97891e+08 | 136998 | 0.126473 | 2.85376 | 4(Loss) | true |
