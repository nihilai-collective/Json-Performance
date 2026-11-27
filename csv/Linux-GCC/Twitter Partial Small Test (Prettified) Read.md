
----
### Twitter Partial Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 8086.04 | 0.101483 | 47.7828ms | 3808 | 160 | 33.2374 | 449.119 | 0.0570236 | 0.289571 | 1(Win) | true |
| simdjson (reflection) | 7960.63 | 0.0996083 | 48.6406ms | 3808 | 160 | 33.0377 | 456.194 | 0.223815 | 0.293504 | 2(Loss) | true |
| Jsonifier | 7544.6 | 0.106862 | 51.753ms | 3808 | 80 | 21.1671 | 481.35 | 0.0207792 | 0.310051 | 3(Loss) | true |
| Jsonifier (two-stage) | 6959.95 | 0.0657431 | 54.9645ms | 3808 | 640 | 75.3118 | 521.784 | 0.144128 | 0.336768 | 4(Loss) | true |
| Glaze | 3883.43 | 0.0270991 | 97.3947ms | 3808 | 640 | 41.1011 | 935.15 | 0.0789266 | 0.620141 | 5(Loss) | true |
