
----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1749.05 | 0.098768 | 6437.48ms | 728486 | 30 | 4.61735e+06 | 397210 | 0.156582 | 1(Win) | true |
| Jsonifier (two-stage) | 1520.11 | 0.284937 | 8280.73ms | 728486 | 640 | 1.08536e+09 | 457032 | 1.62833 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 1305.94 | 0.282579 | 8115.82ms | 728486 | 30 | 6.77956e+07 | 531985 | 0.386461 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1297.63 | 0.207531 | 8173.02ms | 728486 | 640 | 7.90105e+08 | 535390 | 1.2361 | 3(Tie) | true |
| simdjson (ondemand) | 1056.84 | 0.456605 | 9896.24ms | 728486 | 320 | 2.88307e+09 | 657373 | 0.170328 | 5(Loss) | true |
