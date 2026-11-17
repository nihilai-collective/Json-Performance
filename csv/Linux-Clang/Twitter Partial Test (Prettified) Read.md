
----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 11331.8 | 0.168294 | 5487.71ms | 631514 | 640 | 5.12018e+06 | 53147.5 | 0.113139 | 0.218319 | 1(Win) | true |
| Jsonifier | 10879 | 0.352523 | 5543.91ms | 631514 | 80 | 3.04688e+06 | 55359.8 | 0.134212 | 0.227412 | 2(Loss) | true |
| simdjson (ondemand) | 8528.75 | 0.0838037 | 7119.4ms | 631514 | 4890 | 1.7125e+07 | 70615.1 | 0.940165 | 0.290087 | 3(Loss) | true |
| Glaze | 3939.63 | 0.147551 | 7950.81ms | 631514 | 160 | 8.14063e+06 | 152872 | 0.0139106 | 0.628303 | 4(Loss) | true |
