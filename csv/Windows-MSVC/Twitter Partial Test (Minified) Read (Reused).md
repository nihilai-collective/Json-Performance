
----
### Twitter Partial Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 7091.09 | 0.149755 | 6524.4ms | 466906 | 80 | 707429 | 62793.8 | 0.11731 | 0.428411 | 1(Win) | true |
| Jsonifier | 7031.64 | 0.112252 | 6509.43ms | 466906 | 640 | 3.23382e+06 | 63324.7 | 0.0813593 | 0.43206 | 2(Loss) | true |
| simdjson (ondemand) | 4467.28 | 0.107393 | 5277.37ms | 466906 | 40 | 458333 | 99675 | 0.407978 | 0.680203 | 3(Loss) | true |
| Glaze | 2979.19 | 0.148651 | 7777.42ms | 466906 | 2560 | 1.26367e+08 | 149462 | 1.16768 | 1.02 | 4(Loss) | true |
