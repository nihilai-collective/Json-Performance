
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2679.52 | 0.0770013 | 6669.54ms | 183677 | 2560 | 6.48683e+06 | 65373 | 0.181782 | 0.923591 | 1(Win) | true |
| simdjson (ondemand) | 2484.36 | 0.184124 | 7397.36ms | 183677 | 160 | 2.69663e+06 | 70508.4 | 0.0662949 | 0.996197 | 2(Loss) | true |
