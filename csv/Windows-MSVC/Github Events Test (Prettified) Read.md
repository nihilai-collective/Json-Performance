
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1212.47 | 0.224899 | 5150.54ms | 65103 | 4890 | 6.48556e+07 | 51207.2 | 0.760703 | 2.04014 | 1(Win) | true |
| Glaze | 1174.96 | 0.225471 | 5295.85ms | 65103 | 4890 | 6.94138e+07 | 52841.8 | 0.0426032 | 2.10586 | 2(Loss) | true |
| Jsonifier | 1081.8 | 0.322281 | 5770.82ms | 65103 | 2560 | 8.75815e+07 | 57392.1 | 0.051618 | 2.28731 | 3(Loss) | true |
| simdjson (ondemand) | 779.28 | 0.146763 | 7998ms | 65103 | 4890 | 6.68585e+07 | 79672.3 | 0.0837872 | 3.17586 | 4(Loss) | true |
