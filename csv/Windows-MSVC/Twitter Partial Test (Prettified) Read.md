
----
### Twitter Partial Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9842.87 | 0.0877166 | 6148.89ms | 631514 | 4890 | 1.40862e+07 | 61187.3 | 0.317714 | 0.251378 | 1(Win) | true |
| Jsonifier (two-stage) | 9711.57 | 0.0750946 | 6305.75ms | 631514 | 4890 | 1.06051e+07 | 62014.6 | 0.31147 | 0.254773 | 2(Loss) | true |
| simdjson (ondemand) | 3810.58 | 0.0672008 | 8131.09ms | 631514 | 1280 | 1.44392e+07 | 158049 | 0.0863313 | 0.649558 | 3(Loss) | true |
| Glaze | 3569.87 | 0.173197 | 8735.77ms | 631514 | 320 | 2.73206e+07 | 168706 | 0.0294608 | 0.69338 | 4(Loss) | true |
