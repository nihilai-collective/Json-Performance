
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2063.22 | 0.131297 | 1049.42ms | 18245 | 30 | 3678.16 | 8433.33 | 1.24902 | 1.4697 | 1(Win) | true |
| Jsonifier | 1772.44 | 0.467245 | 1170.56ms | 18245 | 160 | 336632 | 9816.88 | 0.197755 | 1.71103 | 2(Loss) | true |
| simdjson (ondemand) | 1280.34 | 0.0824795 | 1562.99ms | 18245 | 40 | 5025.64 | 13590 | 0.418719 | 2.36988 | 3(Loss) | true |
| Glaze | 1048.14 | 0.263588 | 1900.19ms | 18245 | 160 | 306352 | 16600.6 | 0.19994 | 2.89665 | 4(Loss) | true |
