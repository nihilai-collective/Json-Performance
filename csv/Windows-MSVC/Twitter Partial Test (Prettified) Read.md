
----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7682.43 | 0.0558379 | 7839.47ms | 631514 | 4890 | 9.36993e+06 | 78394.3 | 0.220798 | 0.39551 | 1(Win) | true |
| Jsonifier (two-stage) | 7647.27 | 0.136416 | 7878.47ms | 631514 | 320 | 3.69346e+06 | 78754.7 | 0.164402 | 0.397284 | 2(Loss) | true |
| simdjson (ondemand) | 5198.7 | 0.0462842 | 5926.08ms | 631514 | 1280 | 3.68004e+06 | 115848 | 0.0134893 | 0.584524 | 3(Loss) | true |
| Glaze | 3535 | 0.188899 | 8722.28ms | 631514 | 160 | 1.65717e+07 | 170370 | 0.0645237 | 0.859687 | 4(Loss) | true |
