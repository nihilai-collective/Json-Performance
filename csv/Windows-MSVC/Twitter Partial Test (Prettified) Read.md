
----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 9420.37 | 0.282555 | 6772.42ms | 631514 | 320 | 1.04421e+07 | 63931.6 | 0.0981532 | 0.262673 | 1(Win) | true |
| Jsonifier | 8923.1 | 0.131495 | 6826.21ms | 631514 | 1280 | 1.00824e+07 | 67494.3 | 0.255732 | 0.277313 | 2(Loss) | true |
| simdjson (ondemand) | 3675.33 | 0.370134 | 8391.17ms | 631514 | 40 | 1.47146e+07 | 163865 | 0.329468 | 0.673478 | 3(Loss) | true |
| Glaze | 3400.06 | 0.156793 | 9317.9ms | 631514 | 320 | 2.4683e+07 | 177132 | 1.06386 | 0.728022 | 4(Loss) | true |
