
----
### Apache Builds Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2361.13 | 0.141896 | 6257.31ms | 124597 | 40 | 203975 | 50325.4 | 0.0539283 | 1.04802 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 2180.43 | 0.359583 | 6615.91ms | 124597 | 320 | 1.2288e+07 | 54496.2 | 0.277646 | 1.1349 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 2171.19 | 0.247443 | 6590.83ms | 124597 | 2560 | 4.69473e+07 | 54728 | 0.653828 | 1.13972 | 2(Tie) | true |
| Jsonifier (two-stage) | 2162.18 | 0.194167 | 6681.03ms | 124597 | 640 | 7.28723e+06 | 54956.2 | 0.245401 | 1.14448 | 4(Loss) | true |
| Glaze | 1953.66 | 0.152449 | 7266.49ms | 124597 | 640 | 5.50229e+06 | 60821.6 | 0.206992 | 1.2667 | 5(Loss) | true |
