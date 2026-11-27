
----
### Instruments Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4003.79 | 0.186888 | 4538.59ms | 183677 | 640 | 4.27869e+06 | 43750.6 | 0.22253 | 0.617972 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 3993.93 | 0.15258 | 4633.21ms | 183677 | 640 | 2.86605e+06 | 43858.5 | 0.131379 | 0.619501 | 1(Tie) | true |
| simdjson (reflection) | 2618.96 | 0.202727 | 7012.56ms | 183677 | 160 | 2.9417e+06 | 66884.7 | 0.14519 | 0.944955 | 3(Loss) | true |
| Glaze | 2250.6 | 0.110075 | 8007.42ms | 183677 | 4890 | 3.58922e+07 | 77831.8 | 0.341962 | 1.09968 | 4(Loss) | true |
| simdjson (ondemand) | 2117.29 | 0.0538433 | 8514.47ms | 183677 | 4890 | 9.70333e+06 | 82732.2 | 0.0210681 | 1.16894 | 5(Loss) | true |
