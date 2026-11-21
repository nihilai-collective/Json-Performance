
----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 11154.6 | 0.38417 | 5544.65ms | 631514 | 40 | 1.72094e+06 | 53992 | 0.354088 | 0.221796 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 11079.6 | 0.314526 | 5434.68ms | 631514 | 1280 | 3.74144e+07 | 54357.3 | 0.0443899 | 0.223297 | 1(Tie) | true |
| simdjson (ondemand) | 9261.29 | 0.102502 | 6635.2ms | 631514 | 640 | 2.84362e+06 | 65029.7 | 0.250162 | 0.267159 | 3(Loss) | true |
| Glaze | 4183.89 | 0.0657344 | 7354.73ms | 631514 | 2560 | 2.29208e+07 | 143947 | 0.0469545 | 0.591621 | 4(Loss) | true |
