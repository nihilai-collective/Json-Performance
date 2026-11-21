
----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 10261.3 | 0.116182 | 4453.83ms | 466906 | 640 | 1.6267e+06 | 43393.6 | 0.305492 | 0.241126 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 10226.2 | 0.181404 | 4441.85ms | 466906 | 640 | 3.99304e+06 | 43542.6 | 0.00705896 | 0.241955 | 1(Tie) | true |
| simdjson (ondemand) | 7977.49 | 0.0772404 | 5597.97ms | 466906 | 2560 | 4.75835e+06 | 55816.6 | 0.0916968 | 0.310169 | 3(Loss) | true |
| Glaze | 3482.42 | 0.147846 | 6582.55ms | 466906 | 320 | 1.14358e+07 | 127864 | 0.0517909 | 0.710807 | 4(Loss) | true |
