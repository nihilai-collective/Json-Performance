
----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2196.61 | 0.0930019 | 8448.64ms | 183677 | 2560 | 1.40809e+07 | 79744.8 | 0.307457 | 1.12669 | 1(Win) | true |
| Jsonifier | 1922.51 | 0.069507 | 9562.2ms | 183677 | 4890 | 1.96128e+07 | 91114.2 | 0.0408875 | 1.2874 | 2(Loss) | true |
| Glaze | 1586.46 | 0.223395 | 5926.97ms | 183677 | 320 | 1.94691e+07 | 110414 | 0.235749 | 1.56017 | 3(Loss) | true |
| simdjson (ondemand) | 1389.56 | 0.613979 | 7014.84ms | 183677 | 30 | 1.79714e+07 | 126060 | 0.087184 | 1.78142 | 4(Loss) | true |
