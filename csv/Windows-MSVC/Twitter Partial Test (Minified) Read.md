
----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7922.1 | 0.123774 | 5731.92ms | 466906 | 2560 | 1.23901e+07 | 56206.8 | 0.376299 | 0.312329 | 1(Win) | true |
| Jsonifier (two-stage) | 7746.93 | 0.11564 | 5835.56ms | 466906 | 2560 | 1.13098e+07 | 57477.8 | 0.0507927 | 0.319378 | 2(Loss) | true |
| simdjson (ondemand) | 2994.73 | 0.0608723 | 7778.9ms | 466906 | 2560 | 2.09712e+07 | 148687 | 0.271671 | 0.826524 | 3(Loss) | true |
| Glaze | 2607.43 | 0.182263 | 8902.63ms | 466906 | 2560 | 2.48012e+08 | 170772 | 0.0784738 | 0.949302 | 4(Loss) | true |
