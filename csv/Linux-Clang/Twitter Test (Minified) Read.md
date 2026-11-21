
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1798.51 | 0.0688126 | 6448.48ms | 466906 | 640 | 1.8576e+07 | 247581 | 0.0616085 | 1.37631 | 1(Win) | true |
| Jsonifier | 1767.25 | 0.131597 | 6533.46ms | 466906 | 320 | 3.51809e+07 | 251960 | 0.139993 | 1.40067 | 2(Loss) | true |
| Glaze | 1731.61 | 0.0697316 | 6618.56ms | 466906 | 640 | 2.05777e+07 | 257145 | 0.0466469 | 1.42953 | 3(Loss) | true |
| simdjson (ondemand) | 935.01 | 0.0852213 | 6126.26ms | 466906 | 160 | 2.63537e+07 | 476226 | 0.149789 | 2.64765 | 4(Loss) | true |
