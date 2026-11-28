
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1907.19 | 0.101085 | 63.4011ms | 1213 | 160 | 60.1484 | 606.55 | 0.0206126 | 1.24163 | 1(Win) | true |
| simdjson (reflection) | 1123.9 | 0.073876 | 103.689ms | 1213 | 40 | 23.1276 | 1029.28 | 0.186676 | 2.14711 | 2(Loss) | true |
| Glaze | 959.997 | 0.285287 | 124.157ms | 1213 | 2560 | 30254.3 | 1205.01 | 0.116869 | 2.50437 | 3(Loss) | true |
| simdjson (ondemand) | 328.051 | 0.0249175 | 367.226ms | 1213 | 40 | 30.8821 | 3526.3 | 0.00850822 | 7.48965 | 4(Loss) | true |
