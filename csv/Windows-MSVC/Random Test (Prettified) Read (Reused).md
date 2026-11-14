
----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1566.54 | 0.113199 | 6694.05ms | 728486 | 160 | 4.03237e+07 | 443485 | 0.201653 | 1.93989 | 1(Win) | true |
| Jsonifier | 1377.44 | 0.182155 | 7451.38ms | 728486 | 30 | 2.53222e+07 | 504370 | 0.0105731 | 2.20645 | 2(Loss) | true |
| Glaze | 1276.35 | 0.0503463 | 7957.67ms | 728486 | 640 | 4.80637e+07 | 544316 | 0.0206925 | 2.3812 | 3(Loss) | true |
| simdjson (ondemand) | 1110.73 | 0.0704572 | 8955.1ms | 728486 | 640 | 1.24296e+08 | 625480 | 0.120277 | 2.73608 | 4(Loss) | true |
