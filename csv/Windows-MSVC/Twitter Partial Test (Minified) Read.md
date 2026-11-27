
----
### Twitter Partial Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6763.97 | 0.694744 | 6950.65ms | 466906 | 160 | 3.34677e+07 | 65830.6 | 1.5415 | 0.449139 | 1(Win) | true |
| Jsonifier (two-stage) | 6245.33 | 0.969838 | 7020.07ms | 466906 | 1280 | 6.12008e+08 | 71297.5 | 0.610966 | 0.486409 | 2(Loss) | true |
| simdjson (ondemand) | 3968.63 | 1.04956 | 5596.65ms | 466906 | 640 | 8.87509e+08 | 112199 | 0.103997 | 0.765603 | 3(Loss) | true |
| Glaze | 2769.46 | 0.431009 | 8272.66ms | 466906 | 2560 | 1.22937e+09 | 160781 | 1.21888 | 1.09723 | 4(Loss) | true |
