
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2072.55 | 0.171234 | 2597.4ms | 56369 | 4890 | 9.64628e+06 | 25938 | 0.0117115 | 1.19316 | 1(Win) | true |
| Jsonifier (two-stage) | 1695.48 | 0.131066 | 3220.76ms | 56369 | 1280 | 2.21047e+06 | 31706.4 | 0.199344 | 1.45892 | 2(Loss) | true |
| Glaze | 1515.73 | 0.07624 | 3616.27ms | 56369 | 2560 | 1.87174e+06 | 35466.6 | 0.716615 | 1.63198 | 3(Loss) | true |
| simdjson (ondemand) | 786.845 | 0.160916 | 6828.15ms | 56369 | 1280 | 1.54708e+07 | 68320.5 | 0.154852 | 3.14521 | 4(Loss) | true |
