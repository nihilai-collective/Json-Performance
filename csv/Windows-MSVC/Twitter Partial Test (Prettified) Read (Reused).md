
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9402.36 | 0.0946215 | 6640.96ms | 631514 | 2560 | 9.40398e+06 | 64054 | 0.0362112 | 0.263191 | 1(Win) | true |
| Jsonifier (two-stage) | 9247.89 | 0.166412 | 6792.85ms | 631514 | 1280 | 1.50336e+07 | 65123.9 | 0.274508 | 0.267594 | 2(Loss) | true |
| simdjson (ondemand) | 3731.91 | 0.185647 | 8386.77ms | 631514 | 160 | 1.43614e+07 | 161381 | 0.171273 | 0.66328 | 3(Loss) | true |
| Glaze | 3341.37 | 0.26165 | 9184.66ms | 631514 | 160 | 3.5586e+07 | 180243 | 0.319033 | 0.740606 | 4(Loss) | true |
