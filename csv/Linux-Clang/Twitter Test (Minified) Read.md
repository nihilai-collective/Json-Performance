
----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1957.62 | 0.142221 | 5832.54ms | 466906 | 160 | 1.67435e+07 | 227458 | 0.0525979 | 1.26447 | 1(Win) | true |
| Glaze | 1708.23 | 0.111213 | 6769.98ms | 466906 | 320 | 2.68924e+07 | 260665 | 0.352325 | 1.4491 | 2(Loss) | true |
| Jsonifier (two-stage) | 1671.25 | 0.113201 | 6782.44ms | 466906 | 320 | 2.91091e+07 | 266434 | 0.299452 | 1.48114 | 3(Loss) | true |
| simdjson (ondemand) | 925.728 | 0.0740449 | 6105.76ms | 466906 | 320 | 4.05912e+07 | 481001 | 0.0845884 | 2.67417 | 4(Loss) | true |
