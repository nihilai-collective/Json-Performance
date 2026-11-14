
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1691.59 | 0.0927168 | 3184.52ms | 56369 | 4890 | 4.24538e+06 | 31779.4 | 0.273216 | 1(Win) | true |
| Glaze | 1321.66 | 0.4987 | 4139.57ms | 56369 | 320 | 1.31665e+07 | 40674.4 | 0.369157 | 2(Loss) | true |
| Jsonifier (two-stage) | 1165.08 | 0.0772982 | 4620.46ms | 56369 | 4890 | 6.22036e+06 | 46140.7 | 0.121897 | 3(Loss) | true |
| simdjson (reflection) | 1044.38 | 0.695606 | 5593.81ms | 56369 | 30 | 3.84598e+06 | 51473.1 | 0.987778 | 4(Loss) | true |
| simdjson (ondemand) | 917.852 | 0.253204 | 6232.53ms | 56369 | 1280 | 2.81504e+07 | 58569 | 2.36157 | 5(Loss) | true |
